/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define MAKE_COMMAND "make keychron/k8_pro/ansi/rgb:via:flash"
#define MACRO_HOLD_TIMER 75
#include QMK_KEYBOARD_H

/*
 * Tap Dance
 *
 * See:
 * - https://docs.qmk.fm/features/tap_dance#example-4
 *
 */

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_INTERRUPTED_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_INTERRUPTED_DOUBLE_TAP,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    TD_SLASH,
    TD_DOT,
    TD_COMMA,
    TD_QUOTE,
    TD_SEMICOLON,
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the tap dance. Put it here so it can be used in any keymap
void dot_each(tap_dance_state_t *state, void *user_data);
void dot_finished(tap_dance_state_t *state, void *user_data);
void dot_reset(tap_dance_state_t *state, void *user_data);

void comma_each(tap_dance_state_t *state, void *user_data);
void comma_finished(tap_dance_state_t *state, void *user_data);
void comma_reset(tap_dance_state_t *state, void *user_data);

void quote_each(tap_dance_state_t *state, void *user_data);
void quote_finished(tap_dance_state_t *state, void *user_data);
void quote_reset(tap_dance_state_t *state, void *user_data);

void semicolon_each(tap_dance_state_t *state, void *user_data);
void semicolon_finished(tap_dance_state_t *state, void *user_data);
void semicolon_reset(tap_dance_state_t *state, void *user_data);

void nl_minus_each(tap_dance_state_t *state, void *user_data);
void nl_minus_finished(tap_dance_state_t *state, void *user_data);
void nl_minus_reset(tap_dance_state_t *state, void *user_data);

enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  NAVIGATIONS_LAYER,
  SYMBOLS_LAYER,
  NUMS_LAYER,
  FUNCTION_KEYS_LAYER,
  MOUSE_LAYER,
};

#define MT_HL_LINE MT(MOD_LGUI, HL_LINE)
#define MT_HL_LEFT MT(MOD_LALT, HL_LEFT)
#define MT_HL_DOWN MT(MOD_LCTL, HL_DOWN)
#define MT_HL_RIGHT MT(MOD_LSFT, HL_RIGHT)
#define MT_EXCL MT(MOD_LGUI, EXCL)
#define MT_PLUS MT(MOD_LCTL, PLUS)
#define MT_COLON MT(MOD_RSFT, COLON)
#define MT_LBRACE MT(MOD_RCTL, LBRACE)
#define MT_RBRACE MT(MOD_RALT, RBRACE)
#define MT_ATSIGN MT(MOD_RGUI, ATSIGN)

enum custom_keycodes {
    WORD_BSPC = SAFE_RANGE,
    LINE_BSPC,
    WORD_DEL,
    LINE_DEL,
    UNDO,
    REDO,
    EM_DASH,
    HL_LEFT,
    HL_RIGHT,
    HL_HOME,
    HL_END,
    HL_UP,
    HL_DOWN,
    HL_LINE,
    MAKE_KB,
    EXCL,
    PLUS,
    COLON,
    LBRACE,
    RBRACE,
    ATSIGN,
    NEXTSEN,
};

enum combos {
  WE_TAB,
  IL_ENTER,
  QW_ESCAPE,
  MCO_UNDERSCORE,
  NM_UNDERSCORE,
  CODO_SENT,
  FJ_CAPSWORD,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM we_combo[] = {LT(MOUSE_LAYER, KC_W), LT(MOUSE_LAYER, KC_E), COMBO_END};
const uint16_t PROGMEM il_combo[] = {KC_I, MT(MOD_RALT, KC_L), COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, LT(MOUSE_LAYER, KC_W), COMBO_END};
const uint16_t PROGMEM mco_combo[] = {KC_M, TD(TD_COMMA), COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM codo_combo[] = {TD(TD_COMMA), TD(TD_DOT), COMBO_END};
const uint16_t PROGMEM fj_combo[] = {MT(MOD_LSFT, KC_F), MT(MOD_RSFT, KC_J), COMBO_END};

combo_t key_combos[] = {
    [WE_TAB] = COMBO(we_combo, KC_TAB),
    [IL_ENTER] = COMBO(il_combo, KC_ENTER),
    [QW_ESCAPE] = COMBO(qw_combo, KC_ESCAPE),
    [MCO_UNDERSCORE] = COMBO(mco_combo, KC_UNDERSCORE),
    [NM_UNDERSCORE] = COMBO(nm_combo, KC_UNDERSCORE),
    [CODO_SENT] = COMBO(codo_combo, NEXTSEN),
    [FJ_CAPSWORD] = COMBO(fj_combo, QK_CAPS_WORD_TOGGLE),
};

bool is_line_bspc_macro_held = false;
uint16_t line_bspc_macro_timer = 0;
bool is_line_del_macro_held = false;
uint16_t line_del_macro_timer = 0;

bool is_word_bspc_macro_held = false;
uint16_t word_bspc_macro_timer = 0;
bool is_word_del_macro_held = false;
uint16_t word_del_macro_timer = 0;

bool is_hl_up_macro_held = false;
uint16_t hl_up_macro_timer = 0;
bool is_hl_right_macro_held = false;
uint16_t hl_right_macro_timer = 0;
bool is_hl_down_macro_held = false;
uint16_t hl_down_macro_timer = 0;
bool is_hl_left_macro_held = false;
uint16_t hl_left_macro_timer = 0;
bool is_hl_home_macro_held = false;
uint16_t hl_home_macro_timer = 0;
bool is_hl_end_macro_held = false;
uint16_t hl_end_macro_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WORD_BSPC:
            if (record->event.pressed) {
                if (!is_word_bspc_macro_held) {
                    SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
                    is_word_bspc_macro_held = true;
                    word_bspc_macro_timer = timer_read();
                }
                return false;
            } else {
                is_word_bspc_macro_held = false;
                word_bspc_macro_timer = 0;
            }
            break;

        case LINE_BSPC:
            if (record->event.pressed) {
                if (!is_line_bspc_macro_held) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_HOME) SS_TAP(X_HOME)) SS_TAP(X_BACKSPACE));
                    is_line_bspc_macro_held = true;
                    line_bspc_macro_timer = timer_read();
                }
                return false;
            } else {
                is_line_bspc_macro_held = false;
                line_bspc_macro_timer = 0;
            }
            break;

        case WORD_DEL:
            if (record->event.pressed) {
                if (!is_word_del_macro_held) {
                    SEND_STRING(SS_LCTL(SS_TAP(X_DELETE)));
                    is_word_del_macro_held = true;
                    word_del_macro_timer = timer_read();
                }
                return false;
            } else {
                is_word_del_macro_held = false;
                word_del_macro_timer = 0;
            }
            break;

        case LINE_DEL:
            if (record->event.pressed) {
                if (!is_line_del_macro_held) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_END) SS_TAP(X_END)) SS_TAP(X_DELETE));
                    is_line_del_macro_held = true;
                    line_del_macro_timer = timer_read();
                }
                return false;
            } else {
                is_line_del_macro_held = false;
                line_del_macro_timer = 0;
            }
            break;

        case UNDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("z"));
            }
            break;

        case REDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT("z")));
            }
            break;

        case EM_DASH:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_1)));
            }
            break;

        case MT_HL_LEFT:
            if (record->tap.count == 1 && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
                if (!is_hl_left_macro_held) {
                    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
                    is_hl_left_macro_held = true;
                    hl_left_macro_timer = timer_read();
                }
                return false;
            } else {
                is_hl_left_macro_held = false;
                hl_left_macro_timer = 0;
            }
            break;

        case MT_HL_RIGHT:
            if (record->tap.count == 1 && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RGHT))));
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
                if (!is_hl_right_macro_held) {
                    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RGHT))));
                    is_hl_right_macro_held = true;
                    hl_right_macro_timer = timer_read();
                }
                return false;
            } else {
                is_hl_right_macro_held = false;
                hl_right_macro_timer = 0;
            }
            break;

        case HL_HOME:
            if (record->event.pressed) {
                if (!is_hl_home_macro_held) {
                    SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_LEFT)) SS_TAP(X_HOME) SS_TAP(X_HOME)));
                    is_hl_home_macro_held = true;
                    hl_home_macro_timer = timer_read();
                }
                return false;
            } else {
                is_hl_home_macro_held = false;
                hl_home_macro_timer = 0;
            }
            break;

        case HL_END:
            if (record->event.pressed) {
                if (!is_hl_end_macro_held) {
                    SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_RGHT)) SS_TAP(X_END) SS_TAP(X_END)));
                    is_hl_end_macro_held = true;
                    hl_end_macro_timer = timer_read();
                }
                return false;
            } else {
                is_hl_end_macro_held = false;
                hl_end_macro_timer = 0;
            }
            break;

        case HL_UP:
            if (record->event.pressed) {
                if (!is_hl_up_macro_held) {
                    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_UP))));
                    is_hl_up_macro_held = true;
                    hl_up_macro_timer = timer_read();
                }
                return false;
            } else {
                is_hl_up_macro_held = false;
                hl_up_macro_timer = 0;
            }
            break;

        case MT_HL_DOWN:
            if (record->tap.count == 1 && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_DOWN))));
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
                if (!is_hl_down_macro_held) {
                    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_DOWN))));
                    is_hl_down_macro_held = true;
                    hl_down_macro_timer = timer_read();
                }
                return false;
            } else {
                is_hl_down_macro_held = false;
                hl_down_macro_timer = 0;
            }
            break;

        case HL_LINE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END) SS_TAP(X_END)));
            }
            break;

        case MT_HL_LINE:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END) SS_TAP(X_END)));
                return false;
            }
            break;

        case MAKE_KB:
            if (record->event.pressed) {
                SEND_STRING(MAKE_COMMAND);
            }
            break;

        case MT_EXCL:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_1)));
                return false;
            }
            break;

        case MT_PLUS:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_EQL)));
                return false;
            }
            break;

        case MT_COLON:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_SEMICOLON)));
                return false;
            }
            break;

        case MT_LBRACE:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_LBRC)));
                return false;
            }
            break;

        case MT_RBRACE:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_RBRC)));
                return false;
            }
            break;

        case MT_ATSIGN:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_2)));
                return false;
            }
            break;

        case NEXTSEN:
            if (record->event.pressed) {
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT));
                return false;
            }
            break;
    }
    return true;
};

void matrix_scan_user(void) {
  if (is_hl_up_macro_held && timer_elapsed(hl_up_macro_timer) > MACRO_HOLD_TIMER) {
    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_UP))));
    hl_up_macro_timer = timer_read();
  }
  if (is_hl_right_macro_held && timer_elapsed(hl_right_macro_timer) > MACRO_HOLD_TIMER) {
    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RGHT))));
    hl_right_macro_timer = timer_read();
  }
  if (is_hl_down_macro_held && timer_elapsed(hl_down_macro_timer) > MACRO_HOLD_TIMER) {
    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_DOWN))));
    hl_down_macro_timer = timer_read();
  }
  if (is_hl_left_macro_held && timer_elapsed(hl_left_macro_timer) > MACRO_HOLD_TIMER) {
    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
    hl_left_macro_timer = timer_read();
  }

  if (is_hl_home_macro_held && timer_elapsed(hl_home_macro_timer) > MACRO_HOLD_TIMER) {
    SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_LEFT)) SS_TAP(X_HOME) SS_TAP(X_HOME)));
    hl_home_macro_timer = timer_read();
  }
  if (is_hl_end_macro_held && timer_elapsed(hl_end_macro_timer) > MACRO_HOLD_TIMER) {
    SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_RGHT)) SS_TAP(X_END) SS_TAP(X_END)));
    hl_end_macro_timer = timer_read();
  }

  if (is_line_bspc_macro_held && timer_elapsed(line_bspc_macro_timer) > MACRO_HOLD_TIMER * 1.3) {
    SEND_STRING(SS_LSFT(SS_TAP(X_HOME) SS_TAP(X_HOME)) SS_TAP(X_BACKSPACE));
    line_bspc_macro_timer = timer_read();
  }
  if (is_line_del_macro_held && timer_elapsed(line_del_macro_timer) > MACRO_HOLD_TIMER * 1.3) {
    SEND_STRING(SS_LSFT(SS_TAP(X_END) SS_TAP(X_END)) SS_TAP(X_DELETE));
    line_del_macro_timer = timer_read();
  }

  if (is_word_bspc_macro_held && timer_elapsed(word_bspc_macro_timer) > MACRO_HOLD_TIMER * 1.3) {
    SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
    word_bspc_macro_timer = timer_read();
  }
  if (is_word_del_macro_held && timer_elapsed(word_del_macro_timer) > MACRO_HOLD_TIMER * 1.3) {
    SEND_STRING(SS_LCTL(SS_TAP(X_DELETE)));
    word_del_macro_timer = timer_read();
  }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,                KC_SNAP,  KC_SIRI,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,              KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, MO(MAC_FN), KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_ansi(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,                 _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,                 KC_PSCR,  TG(MOUSE_LAYER), RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     LT(MOUSE_LAYER, KC_W),     LT(MOUSE_LAYER, KC_E),     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,
        LT(FUNCTION_KEYS_LAYER, KC_ESC),   MT(MOD_LGUI, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LSFT, KC_F), KC_G,          KC_H,    MT(MOD_RSFT, KC_J),     MT(MOD_RCTL, KC_K),     MT(MOD_RALT, KC_L),     TD(TD_SEMICOLON), TD(TD_QUOTE),              KC_ENT,
        MO(NAVIGATIONS_LAYER),        LT(SYMBOLS_LAYER, KC_Z),     LT(NUMS_LAYER, KC_X),          KC_C,     KC_V,     KC_B,     KC_N,       KC_M,       TD(TD_COMMA),  TD(TD_DOT),   TD(TD_SLASH),              MT(MOD_RSFT, KC_ESC),              KC_UP,
        KC_LCTL,  KC_LCMD,  KC_LALT,                                LT(NUMS_LAYER, KC_SPC),              MO(WIN_FN), KC_RALT, KC_RWIN,   MT(MOD_RCTL, KC_TAB), KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_tkl_ansi(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,                _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        KC_CAPS,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            BT_HST1,  BT_HST2,  BT_HST3,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                RGB_TOG,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [NAVIGATIONS_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  HL_LINE,  HL_HOME,  HL_UP,    HL_END,   _______,  _______,  KC_WH_L,  KC_PGDN,  KC_PGUP,  KC_WH_R,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  MT_HL_LINE, MT_HL_LEFT, MT_HL_DOWN, MT_HL_RIGHT,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_HOME,  KC_END,               _______,
        _______,            UNDO,     _______,  LINE_BSPC,LINE_DEL, WORD_BSPC,KC_BSPC,  KC_DEL,   WORD_DEL, KC_PGDN,  KC_PGUP,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),
    /*
     * Symbol layer loosely based on:
     *   - https://getreuer.info/posts/keyboards/symbol-layer/index.html#my-symbol-layer
     */
    [SYMBOLS_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  KC_GRV,S(KC_COMM),S(KC_DOT), S(KC_MINS),EM_DASH,  _______,  S(KC_7),  S(KC_9),  S(KC_0),  S(KC_5),  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  MT_EXCL,  MT(MOD_LALT, KC_MINS), MT_PLUS,  MT(MOD_LSFT, KC_EQL),  KC_BSLS,  S(KC_BSLS), MT_COLON, MT_LBRACE, MT_RBRACE, MT_ATSIGN, S(KC_QUOT),         _______,
        _______,            S(KC_6),  KC_SLSH,  S(KC_8),  S(KC_3),  S(KC_MINS),S(KC_GRV),S(KC_4), KC_LBRC,  KC_RBRC, S(KC_SLSH),_______,                _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [NUMS_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  _______,  KC_COMM,  KC_DOT,   _______,  _______,  KC_COMMA, KC_7,     KC_8,     KC_9,     S(KC_5),  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  _______,  MT(MOD_LALT, KC_MINS), MT_PLUS, MT(MOD_LSFT, KC_EQL),   _______,  S(KC_4),   MT(MOD_RSFT, KC_4),     MT(MOD_RCTL, KC_5),     MT(MOD_RALT, KC_6),     KC_DOT,  KC_DOT,                 _______,
        _______,            _______,  KC_SLSH,  KC_PAST,  _______,  _______,  KC_0,     KC_1,     KC_2,     KC_3,     KC_SLSH,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [FUNCTION_KEYS_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,    _______,    _______,  _______,  _______,
        _______,  _______,  MT(MOD_LALT, KC_PSCR),        _______,  _______,  _______,  _______,  KC_F4,    KC_F5,    KC_F6,  KC_F11,   KC_F12,               _______,
        _______,            _______,  _______,  MAKE_KB,  _______,  _______,  KC_F10,   KC_F1,    KC_F2,    KC_F3,    _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [MOUSE_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                KC_WH_U,  _______,  KC_WH_D,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    KC_BTN1,  KC_MS_U,  KC_BTN2,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    KC_MS_L,  KC_MS_D,  KC_MS_R,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

};

// See https://docs.qmk.fm/features/tap_dance#example-4
/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_INTERRUPTED_DOUBLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) return TD_INTERRUPTED_SINGLE_TAP;
        if (state->pressed) return TD_SINGLE_HOLD;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        return TD_SINGLE_TAP;
    } else if (state->count == 2) {
        // TD_INTERRUPTED_DOUBLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_INTERRUPTED_DOUBLE_TAP;
        if (state->pressed) return TD_DOUBLE_HOLD;
        return TD_DOUBLE_TAP;
    }
    return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the advanced custom tap dances
static td_tap_t tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void comma_each(tap_dance_state_t *state, void *user_data) {
    if (get_mods() & MOD_MASK_SHIFT) {
        tap_code16(S(KC_COMMA));
        state->count = 0;
        return;
    }
    if (state->count == 3) {
        tap_code(KC_COMMA);
        tap_code(KC_COMMA);
        tap_code(KC_COMMA);
    }
    if (state->count > 3) {
        tap_code(KC_COMMA);
    }
}

void comma_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_COMMA); break;
        case TD_SINGLE_HOLD: layer_on(SYMBOLS_LAYER); break;
        case TD_INTERRUPTED_SINGLE_TAP: register_code(KC_COMMA); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_COMMA)); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_COMMA)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_INTERRUPTED_DOUBLE_TAP: register_code16(S(KC_COMMA)); break;
        default: break;
    }
}

void comma_reset(tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_COMMA); break;
        case TD_SINGLE_HOLD: layer_off(SYMBOLS_LAYER); break;
        case TD_INTERRUPTED_SINGLE_TAP: unregister_code(KC_COMMA); break;
        case TD_DOUBLE_TAP: unregister_code16(S(KC_COMMA)); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_COMMA)); break;
        case TD_INTERRUPTED_DOUBLE_TAP: unregister_code16(S(KC_COMMA)); break;
        default: break;
    }
    tap_state.state = TD_NONE;
}

void dot_each(tap_dance_state_t *state, void *user_data) {
    if (get_mods() & MOD_MASK_SHIFT) {
        tap_code16(S(KC_DOT));
        state->count = 0;
        return;
    }
    if (state->count == 3) {
        tap_code(KC_DOT);
        tap_code(KC_DOT);
        tap_code(KC_DOT);
    }
    if (state->count > 3) {
        tap_code(KC_DOT);
    }
}

void dot_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_DOT); break;
        case TD_SINGLE_HOLD: layer_on(SYMBOLS_LAYER); break;
        case TD_INTERRUPTED_SINGLE_TAP: register_code(KC_DOT); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_DOT)); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_DOT)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_INTERRUPTED_DOUBLE_TAP: register_code16(S(KC_DOT)); break;
        default: break;
    }
}

void dot_reset(tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_DOT); break;
        case TD_SINGLE_HOLD: layer_off(SYMBOLS_LAYER); break;
        case TD_INTERRUPTED_SINGLE_TAP: unregister_code(KC_DOT); break;
        case TD_DOUBLE_TAP: unregister_code16(S(KC_DOT)); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_DOT)); break;
        case TD_INTERRUPTED_DOUBLE_TAP: unregister_code16(S(KC_DOT)); break;
        default: break;
    }
    tap_state.state = TD_NONE;
}

void slash_each(tap_dance_state_t *state, void *user_data) {
    if (get_mods() & MOD_MASK_SHIFT) {
        tap_code16(S(KC_SLASH));
        state->count = 0;
        return;
    }
    if (state->count == 3) {
        tap_code(KC_SLASH);
        tap_code(KC_SLASH);
        tap_code(KC_SLASH);
    }
    if (state->count > 3) {
        tap_code(KC_SLASH);
    }
}

void slash_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SLASH); break;
        case TD_SINGLE_HOLD: layer_on(SYMBOLS_LAYER); break;
        case TD_INTERRUPTED_SINGLE_TAP: layer_on(SYMBOLS_LAYER); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_SLASH)); break;
        case TD_DOUBLE_HOLD: layer_on(SYMBOLS_LAYER); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_INTERRUPTED_DOUBLE_TAP: layer_on(SYMBOLS_LAYER); break;
        default: break;
    }
}

void slash_reset(tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SLASH); break;
        case TD_SINGLE_HOLD: layer_off(SYMBOLS_LAYER); break;
        case TD_INTERRUPTED_SINGLE_TAP: layer_off(SYMBOLS_LAYER); break;
        case TD_DOUBLE_TAP: unregister_code16(S(KC_SLASH)); break;
        case TD_DOUBLE_HOLD: layer_off(SYMBOLS_LAYER); break;
        case TD_INTERRUPTED_DOUBLE_TAP: layer_off(SYMBOLS_LAYER); break;
        default: break;
    }
    tap_state.state = TD_NONE;
}

void semicolon_each(tap_dance_state_t *state, void *user_data) {
    if (get_mods() & MOD_MASK_SHIFT) {
        tap_code16(S(KC_SEMICOLON));
        state->count = 0;
        return;
    }
    if (state->count == 3) {
        tap_code(KC_SEMICOLON);
        tap_code(KC_SEMICOLON);
        tap_code(KC_SEMICOLON);
    }
    if (state->count > 3) {
        tap_code(KC_SEMICOLON);
    }
}

void semicolon_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SEMICOLON); break;
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(KC_RGUI)); break;
        case TD_INTERRUPTED_SINGLE_TAP: register_mods(MOD_BIT(KC_RGUI)); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_SEMICOLON)); break;
        case TD_DOUBLE_HOLD: register_mods(MOD_BIT(KC_RGUI)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_INTERRUPTED_DOUBLE_TAP: register_code16(S(KC_SEMICOLON)); break;
        default: break;
    }
}

void semicolon_reset(tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SEMICOLON); break;
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(KC_RGUI)); break;
        case TD_INTERRUPTED_SINGLE_TAP: unregister_mods(MOD_BIT(KC_RGUI)); break;
        case TD_DOUBLE_TAP: unregister_code16(S(KC_SEMICOLON)); break;
        case TD_DOUBLE_HOLD: unregister_mods(MOD_BIT(KC_RGUI)); break;
        case TD_INTERRUPTED_DOUBLE_TAP: unregister_code16(S(KC_SEMICOLON)); break;
        default: break;
    }
    tap_state.state = TD_NONE;
}

void quote_each(tap_dance_state_t *state, void *user_data) {
    if (get_mods() & MOD_MASK_SHIFT) {
        tap_code16(S(KC_QUOTE));
        state->count = 0;
        return;
    }
    if (state->count == 3) {
        tap_code(KC_QUOTE);
        tap_code(KC_QUOTE);
        tap_code(KC_QUOTE);
    }
    if (state->count > 3) {
        tap_code(KC_QUOTE);
    }
}

void quote_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
        case TD_INTERRUPTED_SINGLE_TAP:
            register_code(KC_QUOTE); break;
        case TD_DOUBLE_TAP: register_code16(S(KC_QUOTE)); break;
        case TD_DOUBLE_HOLD: layer_on(NUMS_LAYER); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_INTERRUPTED_DOUBLE_TAP: layer_on(NUMS_LAYER); break;
        default: break;
    }
}

void quote_reset(tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
        case TD_INTERRUPTED_SINGLE_TAP:
            unregister_code(KC_QUOTE); break;
        case TD_DOUBLE_TAP: unregister_code16(S(KC_QUOTE)); break;
        case TD_DOUBLE_HOLD: layer_off(NUMS_LAYER); break;
        case TD_INTERRUPTED_DOUBLE_TAP: layer_off(NUMS_LAYER); break;
        default: break;
    }
    tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_COMMA] = ACTION_TAP_DANCE_FN_ADVANCED(comma_each, comma_finished, comma_reset),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(dot_each, dot_finished, dot_reset),
    [TD_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(slash_each, slash_finished, slash_reset),
    [TD_SEMICOLON] = ACTION_TAP_DANCE_FN_ADVANCED(semicolon_each, semicolon_finished, semicolon_reset),
    [TD_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(quote_each, quote_finished, quote_reset),
};
