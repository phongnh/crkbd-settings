#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
    #include "lufa.h"
    #include "split_util.h"
#endif
#ifdef SSD1306OLED
    #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;
extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum crkbd_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

enum crkbd_keycodes {
    QWERTY = SAFE_RANGE,
    EPRM,
    RGB_RESET,
};

#define KC______     KC_TRNS
#define KC_XXXXX     KC_NO
#define KC_LOWER     MO(_LOWER)
#define KC_RAISE     MO(_RAISE)
#define KC_RESET     RESET
#define KC_EPRM      EPRM
#define KC_RGB_RESET RGB_RESET
#define KC_RGB_TOG   RGB_TOG
#define KC_RGB_HUI   RGB_HUI
#define KC_RGB_HUD   RGB_HUD
#define KC_RGB_SAI   RGB_SAI
#define KC_RGB_SAD   RGB_SAD
#define KC_RGB_VAI   RGB_VAI
#define KC_RGB_VAD   RGB_VAD
#define KC_RGB_MOD   RGB_MOD
#define KC_RGB_RMO   RGB_RMOD
#define KC_AG_NORM   AG_NORM
#define KC_AG_SWAP   AG_SWAP
#define KC_CTL_ESC   CTL_T(KC_ESC)
#define KC_CTL_Z     CTL_T(KC_Z)
#define KC_CTL_SLS   CTL_T(KC_SLSH)
#define KC_GUI_QUO   GUI_T(KC_QUOT)
#define KC_GUI_HOM   GUI_T(KC_HOME)
#define KC_ALT_END   ALT_T(KC_END)
#define KC_MOU_SCL   LT(_MOUSE, KC_SCLN)     // Turn on _MOUSE layer when held, ; when tapped

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     * │  Tab   │   Q    │   W    │   E    │   R    │   T    │                         │   Y    │   U    │   I    │   O    │   P    │BckSpace│
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │  Esc   │   A    │   S    │   D    │   F    │   G    │                         │   H    │   J    │   K    │   L    │   ;    │   '    │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │ Shift  │   Z    │   X    │   C    │   V    │   B    │                         │   N    │   M    │   ,    │   .    │   \    │ Shift  │
     * └────────┴────────┴────────┴────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘
     *                                     │  Gui   │ LOWER  │  Space │       │ Enter  │  RAISE │  Alt   │
     *                                     └────────┴────────┴────────┘       └────────┴────────┴────────┘
     */
    [_QWERTY] = LAYOUT_kc( \
        TAB,     Q,       W,       E,       R,       T,                                 Y,       U,       I,       O,       P,        BSPC,    \
        CTL_ESC, A,       S,       D,       F,       G,                                 H,       J,       K,       L,       MOU_SCL,  GUI_QUO, \
        LSFT,    CTL_Z,   X,       C,       V,       B,                                 N,       M,       COMM,    DOT,     CTL_SLS,  RSFT,    \
                                            GUI_HOM, LOWER,   SPC,             ENT,     RAISE,   ALT_END                                       \
    ),

    /*
     * ┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     * │   =    │   1    │   2    │   3    │   4    │   5    │                         │   6    │   7    │   8    │   9    │   0    │   -    │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │   `    │        │        │        │        │        │                         │        │        │        │        │        │        │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │        │        │        │        │        │                         │        │        │        │        │        │        │
     * └────────┴────────┴────────┴────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘
     *                                     │        │        │        │       │        │        │        │
     *                                     └────────┴────────┴────────┘       └────────┴────────┴────────┘
     */
    [_LOWER] = LAYOUT_kc( \
        EQL,     1,       2,       3,       4,       5,                                 6,       7,       8,       9,       0,        MINS,  \
        GRV,     F1,      F2,      F3,      F4,      F5,                                F6,      F7,      F8,      F9,      F10,      _____, \
        _____,   F11,     F12,     F13,     F14,     F15,                               F16,     F17,     F18,     F19,     F20,      _____, \
                                            _____,   _____,   _____,           _____,   _____,   _____                                       \
    ),

    /*
     * ┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     * │        │   !    │   @    │   #    │   $    │   %    │                         │   ^    │   &    │   *    │   (    │   )    │        │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │        │  Left  │ Right  │   Up   │  PgUp  │                         │   -    │   =    │   {    │   }    │   |    │   `    │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │        │        │        │  Down  │  PgDn  │                         │   _    │   +    │   [    │   ]    │   \    │   ~    │
     * └────────┴────────┴────────┴────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘
     *                                     │        │        │        │       │        │        │        │
     *                                     └────────┴────────┴────────┘       └────────┴────────┴────────┘
     */
    [_RAISE] = LAYOUT_kc( \
        _____,   EXLM,    AT,      HASH,    DLR,     PERC,                              CIRC,    AMPR,    ASTR,    LPRN,    RPRN,     _____, \
        _____,   XXXXX,   LEFT,    RGHT,    UP,      PGUP,                              MINS,    EQL,     LCBR,    RCBR,    PIPE,     GRV,   \
        _____,   XXXXX,   XXXXX,   XXXXX,   DOWN,    PGDN,                              UNDS,    PLUS,    LBRC,    RBRC,    BSLS,     TILD,  \
                                            _____,   _____,   _____,           _____,   _____,   _____                                       \
    ),

    /*
     * ┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     * │ RESET  │        │        │        │AG NORM │  HUE-  │                         │  HUE+  │AG SWAP │        │        │        │RGB RST │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │CAPSLOCK│        │        │        │RGB RMOD│  SAT-  │                         │  SAT+  │RGB MOD │        │        │        │RGB TOG │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │        │        │        │        │  VAL-  │                         │  VAL+  │        │        │        │        │  EPRM  │
     * └────────┴────────┴────────┴────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘
     *                                     │        │        │        │       │        │        │        │
     *                                     └────────┴────────┴────────┘       └────────┴────────┴────────┘
     */
    [_ADJUST] = LAYOUT_kc( \
        RESET,   XXXXX,   XXXXX,   XXXXX,   AG_NORM, RGB_HUD,                           RGB_HUI, AG_SWAP, XXXXX,    XXXXX,  XXXXX,   RGB_RESET, \
        CAPS,    XXXXX,   XXXXX,   XXXXX,   RGB_RMO, RGB_SAD,                           RGB_SAI, RGB_MOD, XXXXX,    XXXXX,  XXXXX,   RGB_TOG,   \
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   RGB_VAD,                           RGB_VAI, XXXXX,   XXXXX,    XXXXX,  XXXXX,   EPRM,      \
                                            _____,   _____,   _____,           _____,   _____,   _____                                          \
    ),

    /*
     * ┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     * │        │        │ MClick │  MS_U  │ RClick │        │                         │        │ RClick │  WH_U  │ MClick │        │        │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │ LClick │  MS_L  │  MS_D  │  MS_R  │ LClick │                         │ LClick │  WH_L  │  WH_D  │  WH_R  │        │        │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │        │        │        │        │        │                         │        │        │        │        │        │        │
     * └────────┴────────┴────────┴────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘
     *                                     │        │        │        │       │        │        │        │
     *                                     └────────┴────────┴────────┘       └────────┴────────┴────────┘
     */
    [_MOUSE] = LAYOUT_kc( \
        XXXXX,   XXXXX,   XXXXX,   MS_U,    BTN2,    XXXXX,                             XXXXX,   BTN2,    WH_U,    BTN3,    XXXXX,    XXXXX, \
        XXXXX,   BTN1,    MS_L,    MS_D,    MS_R,    BTN1,                              BTN1,    WH_L,    WH_D,    WH_R,    _____,    XXXXX, \
        XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                             XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,    XXXXX, \
                                            _____,   _____,   _____,           _____,   _____,   _____                                       \
    ),

    /*
     * ┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     * │        │        │        │        │        │        │                         │        │        │        │        │        │        │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │        │        │        │        │        │                         │        │        │        │        │        │        │
     * ├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
     * │        │        │        │        │        │        │                         │        │        │        │        │        │        │
     * └────────┴────────┴────────┴────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘
     *                                     │        │        │        │       │        │        │        │
     *                                     └────────┴────────┴────────┘       └────────┴────────┴────────┘
     */
};


void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        // If you want to change the display of OLED, you need to change here
        matrix_write_ln(matrix, read_layer_state());
        matrix_write_ln(matrix, read_keylog());
        matrix_write_ln(matrix, read_keylogs());
        // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
        // matrix_write_ln(matrix, read_host_led_state());
        // matrix_write_ln(matrix, read_timelog());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif // SSD1306OLED

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        #ifdef SSD1306OLED
            set_keylog(keycode, record);
        #endif
        // set_timelog();
    }

    switch (keycode) {
    case QWERTY:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
    case RGB_RESET:
        #ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
        #endif
        return false;
        break;
    case EPRM:
        if (record->event.pressed) {
            eeconfig_init();
        }
        return false;
        break;
    }
    return true;
}
