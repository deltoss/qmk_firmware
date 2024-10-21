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

#include QMK_KEYBOARD_H

enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  NAVIGATIONS_LAYER,
  NUMS_LAYER,
  SYMBOLS_LAYER,
  FUNCTION_KEYS_LAYER,
  MOUSE_LAYER,
};

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
};

#define MT_HL_LEFT MT(MOD_LGUI, HL_LEFT)
#define MT_HL_DOWN MT(MOD_LALT, HL_DOWN)
#define MT_HL_RIGHT MT(MOD_LCTL, HL_RIGHT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WORD_BSPC:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
            }
            break;

        case LINE_BSPC:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_HOME) SS_TAP(X_HOME)) SS_TAP(X_BACKSPACE));
            }
            break;

        case WORD_DEL:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_DELETE)));
            }
            break;

        case LINE_DEL:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_END) SS_TAP(X_END)) SS_TAP(X_DELETE));
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
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
                return false;
            }
            break;

        case MT_HL_RIGHT:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RGHT))));
                return false;
            }
            break;

        case HL_HOME:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_HOME) SS_TAP(X_HOME)));
            }
            break;

        case HL_END:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_END) SS_TAP(X_END)));
            }
            break;

        case HL_UP:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_UP)));
            }
            break;

        case MT_HL_DOWN:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_DOWN)));
                return false;
            }
            break;

        case HL_LINE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END) SS_TAP(X_END)));
            }
            break;
    }
    return true;
};

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
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,
        LT(NUMS_LAYER, KC_ESC),   MT(MOD_LGUI, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LSFT, KC_F), LT(SYMBOLS_LAYER, KC_G),          LT(SYMBOLS_LAYER, KC_H),    MT(MOD_RSFT, KC_J),     MT(MOD_RCTL, KC_K),     MT(MOD_RALT, KC_L),     MT(MOD_RGUI, KC_SCLN),  KC_QUOT,              KC_ENT,
        MO(NAVIGATIONS_LAYER),        KC_Z,     LT(NUMS_LAYER, KC_X),         KC_C,     KC_V,     KC_B,     LT(NUMS_LAYER, KC_N),     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              MT(MOD_RSFT, KC_ESC),              KC_UP,
        MO(FUNCTION_KEYS_LAYER),  KC_LCMD,  KC_LALT,                                KC_SPC,                                 MO(WIN_FN), KC_RALT,  KC_RWIN,  MT(MOD_RCTL, KC_TAB),    KC_LEFT,  KC_DOWN,  KC_RGHT),

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
        HL_LINE,  HL_HOME,  HL_UP,    HL_END,   REDO,     KC_TAB,   _______,  UNDO,     KC_INS,   LINE_BSPC,LINE_DEL, _______,  _______,    _______,    _______,  _______,  _______,
        _______,  MT_HL_LEFT,  MT_HL_DOWN,  MT_HL_RIGHT,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_HOME,  KC_END,               _______,
        _______,            UNDO,     _______,  _______,  WORD_BSPC,WORD_BSPC,KC_BSPC,  KC_DEL,   WORD_DEL, WORD_DEL, HL_LINE,              _______,              _______,
        _______,  _______,  _______,                                KC_ENT,                                 _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [NUMS_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,  _______,    _______,    _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [SYMBOLS_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0),  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  S(KC_7), S(KC_BSLS),_______,  _______,  _______,  _______,  _______,  S(KC_LBRC), S(KC_RBRC),  KC_LBRC, KC_RBRC,          _______,
        _______,            KC_MINS,  S(KC_EQL),KC_EQL,   KC_GRV,   S(KC_MINS),         S(KC_GRV),EM_DASH, S(KC_COMM),          S(KC_DOT),              KC_BSLS,            _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [FUNCTION_KEYS_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,    _______,    _______,  _______,  _______,
        _______,  _______,  KC_PSCR,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_F11,   KC_F12,               _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

    [MOUSE_LAYER] = LAYOUT_tkl_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                KC_WH_U,  _______,  KC_WH_D,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    KC_BTN1,  KC_MS_U,  KC_BTN2,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    KC_MS_L,  KC_MS_D,  KC_MS_R,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    _______,  _______,  _______),

};
