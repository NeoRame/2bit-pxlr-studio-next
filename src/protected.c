#pragma bank 255

#include <gbdk/platform.h>
#include <stdint.h>
#include <stdbool.h>

#include "systemhelpers.h"
#include "gbcamera.h"
#include "vector.h"

#include "protected.h"

void protected_pack(uint8_t * v) BANKED {
    uint8_t i, elem;
    VECTOR_ITERATE(v, i, elem) {
        protected_modify_slot(elem, i);
    }
}

uint16_t protected_scale_line_part(const void * ptr) NAKED {
    ptr;
#ifdef NINTENDO
    __asm
.macro .SHIFT_6_2 reg
        rla
        rla
        rl reg
        rla
        rla
        rla
        rla
        rl reg
.endm
.macro .SCALE regh regl
        ld a, (hl+)
        .SHIFT_6_2 regl
        ld a, (hl-)
        .SHIFT_6_2 regh
.endm
.macro  .ADD_A_HL
        add l
        ld l, a
        adc h
        sub l
        ld h, a
.endm
        ld h, d
        ld l, e

        .rept 3
            .SCALE b,c
            ld a, #16
            .ADD_A_HL
        .endm
        .SCALE b,c

        ret
    __endasm;
#else
    __asm
        ld hl, #0
        ret
    __endasm;
#endif
}

void protected_generate_thumbnail(uint8_t slot) BANKED {
    SWITCH_RAM((slot >> 1) + 1);
    uint16_t * sour = (slot & 1) ? image_second : image_first;
    uint16_t * dest = (slot & 1) ? image_second_thumbnail : image_first_thumbnail;
    for (uint8_t y = 0; y != 28; y++) {
        uint16_t * s = sour + ((uint16_t)((uint8_t)(y * 4) / 8)) * (CAMERA_IMAGE_TILE_WIDTH * 8) + ((y * 4) % 8);
        uint16_t * d = dest + ((uint16_t)(y / 8)) * (CAMERA_THUMB_TILE_WIDTH * 8) + (y % 8);
        for (uint8_t x = 0; x != 4; x++) {
            *d = protected_scale_line_part(s);
            d += 8, s += (4 * 8);
        }
    }
}

uint8_t * copy_data_row(uint8_t * dest, const uint8_t * sour, uint8_t count) NAKED {
    dest; sour; count;
    __asm
        ldhl sp, #2
        ld a, (hl)

        ld h, d
        ld l, e

        ld d, a     ; d == count

1$:
        .rept 16
            ld a, (bc)
            inc bc
            ld (hl+), a
        .endm

        dec d
        jr nz, 1$

        pop hl
        inc sp
        jp (hl)
    __endasm;
}

static uint8_t hflip_loop;
uint8_t * copy_data_row_flipped(uint8_t * dest, const uint8_t * sour, uint8_t count) NAKED {
    dest; sour; count;
    __asm
        ldhl sp, #2
        ld a, (hl)
        ld l, a
        ld h, #0
        .rept 4
            add hl, hl
        .endm
        dec hl
        dec hl
        add hl, de

1$:
        ld (#_hflip_loop), a

        .rept 8
            ld d, #>_flip_recode_table
            .rept 2
                ld a, (bc)
                inc bc
                ld e, a
                ld a, (de)
                ld (hl+), a
            .endm
            ld de, #-4
            add hl, de
        .endm

        ld a, (#_hflip_loop)
        dec a
        jp nz, 1$

        pop hl
        inc sp
        jp (hl)
    __endasm;
}

void protected_lastseen_to_slot(uint8_t slot, bool flipped) BANKED {
    static uint8_t slot_bank, * dest, * sour;
    uint8_t buffer[CAMERA_IMAGE_TILE_WIDTH * 16];

    slot_bank = (slot >> 1) + 1;
    dest = (slot & 1) ? image_second : image_first;
    sour = last_seen;

    if (!flipped) {
        for (uint8_t i = CAMERA_IMAGE_TILE_HEIGHT; i != 0; i--) {
            SWITCH_RAM(CAMERA_BANK_LAST_SEEN);
            copy_data_row(buffer, sour, CAMERA_IMAGE_TILE_WIDTH), sour += sizeof(buffer);
            SWITCH_RAM(slot_bank);
            copy_data_row(dest, buffer, CAMERA_IMAGE_TILE_WIDTH), dest += sizeof(buffer);
        }
        return;
    }
    sour += (CAMERA_IMAGE_TILE_HEIGHT - 1) * (CAMERA_IMAGE_TILE_WIDTH * 16);
    for (uint8_t i = CAMERA_IMAGE_TILE_HEIGHT; i != 0; i--) {
        SWITCH_RAM(CAMERA_BANK_LAST_SEEN);
        copy_data_row_flipped(buffer, sour, CAMERA_IMAGE_TILE_WIDTH), sour -= sizeof(buffer);
        SWITCH_RAM(slot_bank);
        copy_data_row(dest, buffer, CAMERA_IMAGE_TILE_WIDTH), dest += sizeof(buffer);
    }
}

static uint8_t meta_offsets[] = { 8, 2, 2, 2, 10, 2, 2, 2, 10, 2, 2, 2, 10, 2, 2, 2 };

static inline uint8_t * thumbnail_last_row(uint8_t slot) {
    return ((slot & 1) ? image_second_thumbnail : image_first_thumbnail) + ((CAMERA_THUMB_TILE_HEIGHT - 1) * CAMERA_THUMB_TILE_WIDTH * 16);
}

uint8_t protected_metadata_read(uint8_t slot, uint8_t * dest, uint8_t size) BANKED {
    if (!size) return FALSE;
    SWITCH_RAM((slot >> 1) + 1);
    uint8_t * s = thumbnail_last_row(slot);
    for (uint8_t i = 0, sz = size, * d = dest; i < LENGTH(meta_offsets); i++) {
        s += meta_offsets[i];
        *d++ = *s;
        if (!(--sz)) return TRUE;
        *d++ = *(s + 1);
        if (!(--sz)) return TRUE;
    }
    return FALSE;
}

uint8_t protected_metadata_write(uint8_t slot, uint8_t * sour, uint8_t size) BANKED {
    if (!size) return FALSE;
    SWITCH_RAM((slot >> 1) + 1);
    uint8_t * d = thumbnail_last_row(slot);
    for (uint8_t i = 0, sz = size, * s = sour; i < LENGTH(meta_offsets); i++) {
        d += meta_offsets[i];
        *d = *s++;
        if (!(--sz)) return TRUE;
        *(d + 1) = *s++;
        if (!(--sz)) return TRUE;
    }
    return FALSE;
}