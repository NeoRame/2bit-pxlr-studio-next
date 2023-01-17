        .include        "global.s"

        .globl __current_1bpp_colors

        .area   _HOME

.macro .BIT_TO_COLOR reg, bg_reg, fg_reg, ?lbl1
        ld a, fg_reg
        jr c, lbl1
        ld a, bg_reg
lbl1:
.endm

; void set_1bpp_data(uint8_t *first_tile, uint8_t nb_tiles, const uint8_t *data) OLDCALL PRESERVES_REGS(b, c);
_set_1bpp_data::
        push bc

        lda hl, 8(sp)
        ld a, (hl-) ; ID of 1st tile
        ld d, a
        ld a, (hl-) ; ID of 1st tile
        ld e, a
        ld a, (hl-) ; Nb of tiles
        ld c, a
        ld a, (hl-) ; dest ptr
        ld l, (hl)
        ld h, a

1$:
        ; Wrap from past $97FF to $8800 onwards
        ; This can be reduced to "bit 4 must be clear if bit 3 is set"
        bit 3, h
        jr z, 2$
        res 4, h
2$:
        ld b, #8
3$:
        push bc
        push hl

        ld hl, #__current_1bpp_colors
        ld a, (hl+)
        ld h, (hl)
        ld l, a         ; L ==.fg_colour, H == .bg_colour

        ld a, (de)
        ld b, a
        inc de

        rr b
        .rept 8
            .BIT_TO_COLOR b, h, l

            rrca
            rr c
            rrca
            rr b
        .endm

        pop hl

        WAIT_STAT
        ld (hl), c
        inc l
        ld (hl), b
        inc hl

        pop bc

        dec b
        jp nz, 3$

        dec c
        jp nz, 1$

        pop bc
        ret