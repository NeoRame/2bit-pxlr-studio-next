#ifndef __MENUS_H_INCLUDE__
#define __MENUS_H_INCLUDE__

#include <stdint.h>

typedef struct menu_t;
typedef struct menu_item_t;

#define MENU_INVERSE            1

#define MENU_FLAGS_DEFAULT   (MENU_DRAW_FRAME | MENU_DRAW_ITEMS | MENU_DRAW_SELECTION)
#define MENU_FLAGS_NOFRAME   (MENU_DRAW_ITEMS | MENU_DRAW_SELECTION)
#define MENU_FLAGS_NONE      0
#define MENU_DRAW_FRAME      1
#define MENU_DRAW_ITEMS      2
#define MENU_DRAW_SELECTION  4

#define ITEM_DEFAULT            0
#define ITEM_DISABLED           1

typedef uint8_t menu_handler_t (const struct menu_t * self, uint8_t * param);
typedef uint8_t idle_handler_t (const struct menu_t * menu, const struct menu_item_t * selection);
typedef uint8_t menu_translate_t (const struct menu_t * menu, const struct menu_item_t * self, uint8_t value);
typedef uint8_t * item_handler_t (const struct menu_t * menu, const struct menu_item_t * self);
typedef uint8_t query_handler_t (const struct menu_t * menu, const struct menu_item_t * self);

typedef struct menu_item_t {
    struct menu_t * sub;
    uint8_t * sub_params;
    uint8_t ofs_x;
    uint8_t ofs_y;
    uint8_t width;
    uint8_t id;
    const uint8_t * caption;
    const uint8_t * helpcontext;
    item_handler_t * onPaint;
    query_handler_t * onGetProps;
    uint8_t result;
} menu_item_t;

typedef struct menu_t {
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    uint8_t cancel_mask;
    uint8_t cancel_result;
    uint8_t flags;
    menu_item_t * items;
    menu_item_t * last_item;
    menu_handler_t * onShow;
    idle_handler_t * onIdle;
    idle_handler_t * onHelpContext;
    menu_translate_t * onTranslateKey;
    menu_translate_t * onTranslateSubResult;
} menu_t;

void menu_text_out(uint8_t x, uint8_t y, uint8_t w, uint8_t c, const uint8_t * text);
const menu_item_t * menu_move_selection(const menu_t * menu, const menu_item_t * selection, const menu_item_t * new_selection);
void menu_draw_frame(const menu_t * menu);


typedef enum {
    changeNone = 0,
    changeDecrease,
    changeIncrease
} change_direction_e;

inline uint8_t inc_dec_int8(int8_t * value, int8_t delta, int8_t min, int8_t max, change_direction_e dir) {
    int8_t v = *value;
    switch (dir) {
        case changeDecrease:
            return (v != (*value = ((*value - delta) < min) ? max : (*value - delta)));
        case changeIncrease:
            return (v != (*value = ((*value + delta) > max) ? min : (*value + delta)));
        default:
            return FALSE;
    }
}
inline uint8_t inc_dec_int16(int16_t * value, int16_t delta, int16_t min, int16_t max, change_direction_e dir) {
    int16_t v = *value;
    switch (dir) {
        case changeDecrease:
            *value = ((*value - delta) < min) ? max : (*value - delta);
            break;
        case changeIncrease:
            *value = ((*value + delta) > max) ? min : (*value + delta);
            break;
    }
    return (v != *value);
}


uint8_t menu_execute(const menu_t * menu, uint8_t * param, const menu_item_t * select);

#endif