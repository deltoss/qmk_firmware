/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define MAKE_COMMAND "qmk flash -kb crkbd/rev4_1/standard -km default"
#define MACRO_HOLD_TIMER 75
#include QMK_KEYBOARD_H

enum layers{
  BASE,
  NAVIGATIONS_LAYER,
  SYMBOLS_LAYER,
  NUMS_LAYER,
  FUNCTION_KEYS_LAYER,
  MOUSE_LAYER,
  BASE_FN,
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
#define LT_NAVIGATIONS_UNDERSCORE LT(NAVIGATIONS_LAYER, UNDERSCORE)
#define LT_WORD_BSPC LT(NUMS_LAYER, WORD_BSPC)
#define LT_WORD_DEL LT(NUMS_LAYER, WORD_DEL)

enum custom_keycodes {
    WORD_BSPC = SAFE_RANGE,
    LINE_BSPC,
    WORD_DEL,
    LINE_DEL,
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
    UNDERSCORE,
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

const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM il_combo[] = {KC_I, MT(MOD_RALT, KC_L), COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM mco_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM codo_combo[] = {KC_COMM, KC_DOT, COMBO_END};
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
        case LT_WORD_BSPC:
            if (record->tap.count == 1 && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
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

        case LT_WORD_DEL:
            if (record->tap.count == 1 && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_DELETE)));
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
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

        case LT_NAVIGATIONS_UNDERSCORE:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_MINS)));
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LT(MOUSE_LAYER, KC_ESC),  MT(MOD_LGUI, KC_A),    MT(MOD_LALT, KC_S),    MT(MOD_LCTL, KC_D),    MT(MOD_LSFT, KC_F),    KC_G,                         KC_H,    MT(MOD_RSFT, KC_J),    MT(MOD_RCTL, KC_K),    MT(MOD_RALT, KC_L), MT(MOD_RGUI, KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LT_NAVIGATIONS_UNDERSCORE, LT(SYMBOLS_LAYER, KC_Z),    LT(NUMS_LAYER, KC_X),    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMMA,  KC_DOT, LT(SYMBOLS_LAYER, KC_SLSH), MO(FUNCTION_KEYS_LAYER),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          LT_WORD_BSPC,  LT(SYMBOLS_LAYER, KC_BSPC),  LT(NAVIGATIONS_LAYER, KC_SPC),     LT(NAVIGATIONS_LAYER, KC_ENT),   LT(SYMBOLS_LAYER, KC_DEL), LT_WORD_DEL
                                      //`--------------------------'  `--------------------------'

  ),

    [NAVIGATIONS_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, HL_LINE, HL_HOME, HL_UP,    HL_END, _______,                    _______, KC_WH_L, KC_PGDN, KC_PGUP, KC_WH_R, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, MT_HL_LINE, MT_HL_LEFT, MT_HL_DOWN, MT_HL_RIGHT, KC_BSPC,           KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_HOME, KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        LINE_BSPC, _______, _______,    _______, _______, LINE_DEL
                                      //`--------------------------'  `--------------------------'
  ),

    /*
     * Symbol layer loosely based on:
     *   - https://getreuer.info/posts/keyboards/symbol-layer/index.html#my-symbol-layer
     */
    [SYMBOLS_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_GRV, S(KC_COMM), S(KC_DOT), S(KC_MINS), EM_DASH,               _______, S(KC_7), S(KC_9), S(KC_0), S(KC_5), _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, MT_EXCL, MT(MOD_LALT, KC_MINS), MT_PLUS, MT(MOD_LSFT, KC_EQL), KC_BSLS,                      S(KC_BSLS), MT_COLON, MT_LBRACE, MT_RBRACE, MT_ATSIGN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, S(KC_6), KC_SLSH, S(KC_8), S(KC_3), S(KC_MINS),                   S(KC_GRV), S(KC_4), KC_LBRC, KC_RBRC, S(KC_SLSH), S(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [NUMS_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, KC_COMM, KC_DOT, _______, _______,                      KC_COMMA,    KC_7,    KC_8,    KC_9, S(KC_5), _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, MT(MOD_LALT, KC_MINS), MT_PLUS, MT(MOD_LSFT, KC_EQL), _______,                      S(KC_4), MT(MOD_RSFT, KC_4), MT(MOD_RCTL, KC_5), MT(MOD_RALT, KC_6), KC_DOT, KC_DOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_SLSH, KC_PAST, _______, _______,                      KC_0, KC_1, KC_2, KC_3, KC_SLSH, KC_DOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      MO(BASE_FN), _______, _______,    _______, _______, MO(BASE_FN)
                                      //`--------------------------'  `--------------------------'
  ),

    [FUNCTION_KEYS_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, MT(MOD_LALT, KC_PSCR), _______, _______, _______,        _______,   KC_F4,   KC_F5,   KC_F6, KC_F11, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, MAKE_KB, _______, _______,                      _______,   KC_F1,   KC_F2,   KC_F3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [MOUSE_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, MT(MOD_LCTL, KC_BTN2), MT(MOD_LSFT, KC_BTN2), _______,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_BTN2, KC_BTN1,    KC_BTN1, KC_BTN2, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [BASE_FN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NAVIGATIONS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [SYMBOLS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NUMS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [FUNCTION_KEYS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [MOUSE_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [BASE_FN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
        case MT(MOD_LGUI, KC_A):
        case MT(MOD_LALT, KC_S):
        case MT(MOD_LCTL, KC_D):
        case MT(MOD_LSFT, KC_F):
        case MT(MOD_RSFT, KC_J):
        case MT(MOD_RCTL, KC_K):
        case MT(MOD_RALT, KC_L):
        case MT(MOD_RGUI, KC_SCLN):
        case LT(SYMBOLS_LAYER, KC_SLSH):
        case LT(SYMBOLS_LAYER, KC_Z):
        case LT(NUMS_LAYER, KC_X):
            return true;
        default:
            return false;
    }
}
