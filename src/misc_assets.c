#pragma bank 255

#include <gbdk/platform.h>
#include <stdint.h>

#include "screen.h"

static const uint8_t screen_tiles[] = {
    0x00,0x00,0x7D,0x7D,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x40,0x40,
    0x00,0x00,0xBE,0xBE,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x02,0x02,
    0x02,0x02,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xBE,0xBE,0x00,0x00,
    0x40,0x40,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7D,0x7D,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

void misc_assets_init() BANKED {
#ifdef NINTENDO
    set_data(TO_TILE_ADDRESS(_VRAM8000, 256 - (sizeof(screen_tiles) >> 4)), screen_tiles, sizeof(screen_tiles));
#endif
}
