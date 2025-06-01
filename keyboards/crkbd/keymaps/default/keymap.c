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
  GAME_LAYER,
  GAME_NUM_LAYER,
  NAVIGATIONS_LAYER,
  SYMBOLS_LAYER,
  NUMS_LAYER,
  FUNCTION_KEYS_LAYER,
  MOUSE_LAYER,
  BASE_FN,
};

#define MT_SLSH MT(MOD_LGUI, SLASH)
#define MT_PLUS MT(MOD_LCTL, PLUS)
#define MT_DQUO MT(MOD_RSFT, DQUO)
#define MT_LBRACE MT(MOD_RCTL, LBRACE)
#define MT_RBRACE MT(MOD_RALT, RBRACE)
#define MT_CLN MT(MOD_RGUI, CLN)
#define LT_UNDERSCORE LT(NUMS_LAYER, UNDERSCORE)
#define MT_WORD_BSPC MT(MOD_HYPR, WORD_BSPC)
#define LT_WORD_DEL LT(NUMS_LAYER, WORD_DEL)
#define LT_OSM LT(MOUSE_LAYER, KC_NO)
#define LT_VW_TABS LT(NAVIGATIONS_LAYER, VW_TABS)
#define QUAKE LGUI(KC_GRV)
#define MT_REDO MT(MOD_LGUI, REDO)
#define MT_CUT MT(MOD_LALT, CUT)
#define MT_COPY MT(MOD_LCTL, COPY)
#define MT_PASTE MT(MOD_LSFT, PASTE)

enum custom_keycodes {
    WORD_BSPC = SAFE_RANGE,
    WORD_DEL,
    SLASH,
    PLUS,
    DQUO,
    LBRACE,
    RBRACE,
    CLN,
    UNDERSCORE,
    OSM_SHIFT,
    QUIT_TAB,
    QUIT_APP,
    VW_TABS,
    SWITCH_TAB,
    CUT,
    COPY,
    PASTE,
    SPASTE,
    RENAME,
    MNMIZE,
    UNDO,
    REDO,
    SREDO,
    SELA,
    NAV_BACK,
    NAV_FORTH,
    NAV_UP,
    ARW_RHT,
};

enum combos {
  TAB_COMBO,
  ENTER_COMBO,
  APP_COMBO,
  FNKEYSLYR_COMBO,
  SENT_COMBO,
  AUTOSHIFT_COMBO,
  GAMELYR_COMBO,
  RHT_MOUSELYR_COMBO,
  LFT_MOUSELYR_COMBO,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM ld_combo[] = {KC_L, KC_D, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, MT(MOD_RALT, KC_E), COMBO_END};
const uint16_t PROGMEM kp_combo[] = {KC_K, KC_P, COMBO_END};
const uint16_t PROGMEM pcom_combo[] = {KC_P, KC_COMM, COMBO_END};
const uint16_t PROGMEM comdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM insj_combo[] = {KC_INS, KC_J, COMBO_END};
const uint16_t PROGMEM insscln_combo[] = {KC_INS, KC_SCLN, COMBO_END};
const uint16_t PROGMEM rthumbs_combo[] = {LT(NAVIGATIONS_LAYER, KC_ENT), LT(SYMBOLS_LAYER, KC_DEL), LT_WORD_DEL, COMBO_END};
const uint16_t PROGMEM lthumbs_combo[] = {MT_WORD_BSPC, MT(MOD_MEH, KC_BSPC), MT(MOD_LSFT, KC_SPC), COMBO_END};

combo_t key_combos[] = {
    [TAB_COMBO] = COMBO(ld_combo, KC_TAB),
    [ENTER_COMBO] = COMBO(oe_combo, KC_ENTER),
    [APP_COMBO] = COMBO(kp_combo, KC_APP),
    [FNKEYSLYR_COMBO] = COMBO(pcom_combo, OSL(FUNCTION_KEYS_LAYER)),
    [SENT_COMBO] = COMBO(comdot_combo, QK_LEAD),
    [AUTOSHIFT_COMBO] = COMBO(insj_combo, AS_TOGG),
    [GAMELYR_COMBO] = COMBO(insscln_combo, TG(GAME_LAYER)),
    [RHT_MOUSELYR_COMBO] = COMBO(rthumbs_combo, TG(MOUSE_LAYER)),
    [LFT_MOUSELYR_COMBO] = COMBO(lthumbs_combo, TG(MOUSE_LAYER)),
};

bool is_word_bspc_macro_held = false;
uint16_t word_bspc_macro_timer = 0;
bool is_word_del_macro_held = false;
uint16_t word_del_macro_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_WORD_BSPC:
            if (record->tap.count == 1 && record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_HOME) SS_TAP(X_BACKSPACE));
                } else {
                    SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
                }
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
                if (!is_word_bspc_macro_held) {
                    if (get_mods() & MOD_MASK_SHIFT) {
                        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_HOME) SS_TAP(X_BACKSPACE));
                    } else {
                        SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
                    }
                    is_word_bspc_macro_held = true;
                    word_bspc_macro_timer = timer_read();
                }
                return false;
            } else {
                is_word_bspc_macro_held = false;
                word_bspc_macro_timer = 0;
            }
            break;

        case LT_WORD_DEL:
            if (record->tap.count == 1 && record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    SEND_STRING(SS_TAP(X_END) SS_TAP(X_END) SS_TAP(X_DELETE));
                } else {
                    SEND_STRING(SS_LCTL(SS_TAP(X_DELETE)));
                }
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
                if (!is_word_del_macro_held) {
                    if (get_mods() & MOD_MASK_SHIFT) {
                        SEND_STRING(SS_TAP(X_END) SS_TAP(X_END) SS_TAP(X_DELETE));
                    } else {
                        SEND_STRING(SS_LCTL(SS_TAP(X_DELETE)));
                    }
                    is_word_del_macro_held = true;
                    word_del_macro_timer = timer_read();
                }
                return false;
            } else {
                is_word_del_macro_held = false;
                word_del_macro_timer = 0;
            }
            break;

        case MT_SLSH:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_TAP(X_SLSH));
                return false;
            }
            break;

        case MT_PLUS:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_EQL)));
                return false;
            }
            break;

        case MT_DQUO:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_QUOT)));
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

        case MT_CLN:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_SCLN)));
                return false;
            }
            break;

        case LT_UNDERSCORE:
            if (record->tap.count && record->event.pressed) { // Tap
                // Check the activation of either shift keys
                if (get_mods() & MOD_MASK_SHIFT) {
                    SEND_STRING(SS_TAP(X_MINS));
                } else {
                    SEND_STRING(SS_LSFT(SS_TAP(X_MINS)));
                }
                return false;
            } else if (record->event.pressed) { // Hold
                register_mods(MOD_LGUI);
            } else { // Release
                unregister_mods(MOD_LGUI);
            }
            break;

        case LT_OSM:
            if (record->tap.count == 1 && record->event.pressed) {
                if (get_oneshot_mods() & MOD_MASK_SHIFT || is_caps_word_on()) {
                    clear_oneshot_mods();
                    caps_word_off();
                } else {
                    add_oneshot_mods(MOD_BIT(KC_LSFT));
                }
                return false;
            } else if (record->tap.count > 1 && record->event.pressed) {
                clear_oneshot_mods();
                caps_word_on();
                return false;
            }
            break;

        case LT_VW_TABS:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_TAB))));
                return false;
            } else if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_TAB))));
                layer_on(NAVIGATIONS_LAYER);
                return false;
            } else if (layer_state_is(NAVIGATIONS_LAYER)) {
                layer_off(NAVIGATIONS_LAYER);
                SEND_STRING(SS_TAP(X_ENTER));
            }
            break;

        case ARW_RHT:
            if (record->event.pressed) {
                // To avoid issues like cursor moving, ensure numlock is ON before executing this macro.
                SEND_STRING(SS_LALT(SS_TAP(X_KP_2) SS_TAP(X_KP_6)));
            }
            break;

       case MT_CUT:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_X)));
                return false;
            }
            break;

       case MT_COPY:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_C)));
                return false;
            }
            break;

       case MT_PASTE:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_V)));
                return false;
            }
            break;

       case SPASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_LCTL(SS_TAP(X_V))));
            }
            break;

       case UNDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_Z)));
            }
            break;

       case MT_REDO:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_Y)));
                return false;
            }
            break;

       case SREDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_Z))));
            }
            break;

       case SELA:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_A)));
            }
            break;

       case RENAME:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F2));
            }
            break;

       case MNMIZE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                SEND_STRING(SS_TAP(X_N));
            }
            break;
    }

    return true;

};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

void oneshot_mods_changed_user(uint8_t mods) {
    if (mods) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
    }
}

void caps_word_set_user(bool active) {
    if (active) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
    }
}

void matrix_scan_user(void) {
  if (is_word_bspc_macro_held && timer_elapsed(word_bspc_macro_timer) > MACRO_HOLD_TIMER * 1.3) {
    if (get_mods() & MOD_MASK_SHIFT) {
        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_HOME) SS_TAP(X_BACKSPACE));
    } else {
        SEND_STRING(SS_LCTL(SS_TAP(X_BACKSPACE)));
    }
    word_bspc_macro_timer = timer_read();
  }
  if (is_word_del_macro_held && timer_elapsed(word_del_macro_timer) > MACRO_HOLD_TIMER * 1.3) {
    if (get_mods() & MOD_MASK_SHIFT) {
        SEND_STRING(SS_TAP(X_END) SS_TAP(X_END) SS_TAP(X_DELETE));
    } else {
        SEND_STRING(SS_LCTL(SS_TAP(X_DELETE)));
    }
    word_del_macro_timer = timer_read();
  }
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MT(MOD_LGUI, KC_N):
        case MT(MOD_LALT, KC_R):
        case MT(MOD_LCTL, KC_T):
        case MT(MOD_LSFT, KC_S):
        case MT(MOD_RSFT, KC_H):
        case MT(MOD_RCTL, KC_A):
        case MT(MOD_RALT, KC_E):
        case MT(MOD_RGUI, KC_I):
        case QUIT_TAB:
        case QUIT_APP:
        case SWITCH_TAB:
        case NAV_BACK:
        case NAV_FORTH:
        case NAV_UP:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case QUIT_TAB:
            if (shifted) {
                SEND_STRING(SS_LCTL(SS_TAP(X_W)));
            } else {
                SEND_STRING(SS_LCTL(SS_TAP(X_F4)));
            }
            break;
        case QUIT_APP:
            if (shifted) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_W))));
            } else {
                SEND_STRING(SS_LALT(SS_TAP(X_F4)));
            }
            break;
        case SWITCH_TAB:
            if (shifted) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))));
            } else {
                SEND_STRING(SS_LCTL(SS_TAP(X_TAB)));
            }
            break;
       case NAV_BACK:
            if (shifted) {
                tap_code(MS_BTN4);
            } else {
                SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
            }
            break;
       case NAV_FORTH:
            if (shifted) {
                tap_code(MS_BTN5);
            } else {
                SEND_STRING(SS_LALT(SS_TAP(X_RGHT)));
            }
            break;
       case NAV_UP:
            SEND_STRING(SS_LALT(SS_TAP(X_UP)));
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_0:
            unregister_code16((!shifted) ? KC_0 : KC_GRAVE);
            break;
        case KC_1:
            unregister_code16((!shifted) ? KC_1 : KC_4);
            break;
        case KC_2:
            unregister_code16((!shifted) ? KC_2 : KC_COMM);
            break;
        case KC_3:
            unregister_code16((!shifted) ? KC_3 : KC_DOT);
            break;
        case MT(MOD_RSFT, KC_4):
            unregister_code16((!shifted) ? MT(MOD_RSFT, KC_4) : KC_2);
            break;
        case MT(MOD_RCTL, KC_5):
            unregister_code16((!shifted) ? MT(MOD_RCTL, KC_5) : KC_LBRC);
            break;
        case MT(MOD_RALT, KC_6):
            unregister_code16((!shifted) ? MT(MOD_RALT, KC_6) : KC_RBRC);
            break;
        case KC_7:
            unregister_code16((!shifted) ? KC_7 : KC_7);
            break;
        case KC_8:
            unregister_code16((!shifted) ? KC_8 : KC_9);
            break;
        case KC_9:
            unregister_code16((!shifted) ? KC_9 : KC_0);
            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(MOUSE_LAYER, KC_ESC):
            return 0;
        case LT_OSM:
            return QUICK_TAP_TERM / 1.5;
        case MT(MOD_LSFT, KC_SPC):
            return QUICK_TAP_TERM / 2;
        default:
            return QUICK_TAP_TERM;
    }
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_DOT)) {
        // Next sentence
        SEND_STRING(". ");
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    } else if (leader_sequence_one_key(KC_W)) {
        SEND_STRING(SS_LCTL(SS_TAP(X_F4)));
    } else if (leader_sequence_one_key(KC_Q)) {
        SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    } else if (leader_sequence_one_key(KC_C)) {
        SEND_STRING(MAKE_COMMAND);
    } else if (leader_sequence_one_key(KC_SLSH)) {
        tap_code16(QUAKE);
    }

    // docker
    if (leader_sequence_two_keys(KC_D, KC_P)) {
        SEND_STRING("docker ps -a");
    } else if (leader_sequence_two_keys(KC_D, KC_L)) {
        SEND_STRING("docker logs [ContainerNameOrId]");
    } else if (leader_sequence_two_keys(KC_D, KC_T)) {
        SEND_STRING("docker exec -it [ContainerNameOrId] sh");
    } else if (leader_sequence_two_keys(KC_D, KC_E)) {
        SEND_STRING("docker exec [ContainerNameOrId] env");
    } else if (leader_sequence_two_keys(KC_D, KC_S)) {
        SEND_STRING("docker stop $(docker ps -a -q)");
    } else if (leader_sequence_two_keys(KC_D, KC_R)) {
        SEND_STRING("docker rmi --force $(docker images -a -q)");
    }

    // docker-compose
    if (leader_sequence_three_keys(KC_D, KC_C, KC_P)) {
        SEND_STRING("docker-compose ps");
    } else if (leader_sequence_three_keys(KC_D, KC_C, KC_L)) {
        SEND_STRING("docker-compose logs");
    } else if (leader_sequence_three_keys(KC_D, KC_C, KC_T)) {
        SEND_STRING("docker-compose exec [ServiceName] sh");
    } else if (leader_sequence_three_keys(KC_D, KC_C, KC_E)) {
        SEND_STRING("docker-compose exec [ServiceName] env");
    } else if (leader_sequence_three_keys(KC_D, KC_C, KC_D)) {
        SEND_STRING("docker-compose down");
    } else if (leader_sequence_three_keys(KC_D, KC_C, KC_D)) {
        SEND_STRING("docker-compose down --volumes --rmi all");
    }
}

// ~0 as layer means to activate on all layers
const key_override_t delete_key_override = ko_make_basic(MOD_LSFT, MT(MOD_MEH, KC_BSPC), KC_DEL);
const key_override_t backspace_key_override = ko_make_basic(MOD_RSFT, LT(SYMBOLS_LAYER, KC_DEL), KC_BSPC);
const key_override_t enter_key_override = ko_make_with_layers_and_negmods(MOD_LSFT | MOD_LCTL, LT(NAVIGATIONS_LAYER, KC_SPC), KC_ENTER, ~0, MOD_MASK_AG);
const key_override_t ctrl_enter_key_override = ko_make_with_layers_and_negmods(MOD_LCTL, LT(NAVIGATIONS_LAYER, KC_SPC), LCTL(KC_ENTER), ~0, MOD_MASK_AG);
const key_override_t sft_enter_key_override = ko_make_with_layers_and_negmods(MOD_LSFT, LT(NAVIGATIONS_LAYER, KC_SPC), S(KC_ENTER), ~0, MOD_MASK_AG);

// This globally defines all key overrides to be used (Window + Space/Backspace)
const key_override_t *key_overrides[] = {
    &delete_key_override,
    &backspace_key_override,
    &enter_key_override,
    &ctrl_enter_key_override,
    &sft_enter_key_override
};

// Graphite-based layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      KC_PSCR,    KC_B,    KC_L,    KC_D,    KC_W,    KC_Z, SWITCH_TAB,            QUIT_TAB, KC_QUOT,    KC_F,    KC_O,    KC_U,    KC_J,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      LT_UNDERSCORE, MT(MOD_LGUI, KC_N), MT(MOD_LALT, KC_R), MT(MOD_LCTL, KC_T), MT(MOD_LSFT, KC_S), KC_G, LT_VW_TABS,       QUIT_APP, KC_Y, MT(MOD_RSFT, KC_H), MT(MOD_RCTL, KC_A), MT(MOD_RALT, KC_E), MT(MOD_RGUI, KC_I), KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      LT(MOUSE_LAYER, KC_ESC), KC_Q, KC_X, KC_M, KC_C, KC_V,                                    KC_K,    KC_P, KC_COMM,  KC_DOT, KC_SLSH,  LT_OSM,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
       MT_WORD_BSPC, MT(MOD_MEH, KC_BSPC), LT(NAVIGATIONS_LAYER, KC_SPC),    LT(NAVIGATIONS_LAYER, KC_ENT), LT(SYMBOLS_LAYER, KC_DEL), LT_WORD_DEL
                                      //`--------------------------------'  `--------------------------------'

  ),

    [GAME_LAYER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      KC_LSFT,    KC_B,    KC_L,    KC_D,    KC_W,    KC_Z, KC_LCTL,                   KC_2, KC_QUOT,    KC_F,    KC_O,    KC_U,    KC_J,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      KC_MINS,    KC_N,    KC_R,    KC_T,    KC_S,    KC_G, KC_LALT,                   KC_3,    KC_Y,    KC_H,    KC_A,    KC_E,    KC_I, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_Q,    KC_X,    KC_M,    KC_C,    KC_V,                                     KC_K,    KC_P, KC_COMM,  KC_DOT, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                     MO(GAME_NUM_LAYER), KC_BSPC, KC_SPC,    KC_ENT, KC_DEL, MO(GAME_NUM_LAYER)
                                      //`--------------------------------'  `--------------------------------'

  ),

    [GAME_NUM_LAYER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      KC_PSCR,   KC_F4,    KC_7,    KC_8,    KC_9,   KC_F1, _______,                _______, _______,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      _______,   KC_F5,    KC_4,    KC_5,    KC_6,   KC_F2, _______,                _______, _______,    KC_4,    KC_5,    KC_6,   KC_F6, _______,
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      _______,    KC_0,    KC_1,    KC_2,    KC_3,   KC_F3,                                     KC_0,    KC_1,    KC_2,    KC_3,   KC_F7, _______,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,    _______, _______, _______
                                      //`--------------------------------'  `--------------------------------'

  ),

    [NAVIGATIONS_LAYER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      _______,   SREDO, _______,    SELA,  RENAME, _______, KC_VOLU,                KC_MPLY,  MNMIZE, KC_WH_L, KC_PGDN, KC_PGUP, KC_WH_R, KC_MPRV,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      _______, MT_REDO,  MT_CUT, MT_COPY, MT_PASTE, SPASTE, KC_VOLD,                KC_MSEL, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_HOME,  KC_END,
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      _______,    UNDO, NAV_BACK, NAV_FORTH, NAV_UP, _______,                                 NAV_UP, NAV_BACK, NAV_FORTH, _______, _______, KC_MNXT,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,    _______, _______, _______
                                      //`--------------------------------'  `--------------------------------'
  ),

    /*
     * Symbol layer loosely based on:
     *   - https://getreuer.info/posts/keyboards/symbol-layer/index.html#my-symbol-layer
     */
    [SYMBOLS_LAYER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      _______, S(KC_MINS), S(KC_COMM), S(KC_DOT), S(KC_2), ARW_RHT, _______,        _______, S(KC_QUOT), S(KC_7), S(KC_9), S(KC_0), XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      _______, MT_SLSH, MT(MOD_LALT, KC_MINS), MT_PLUS, MT(MOD_LSFT, KC_EQL), KC_GRV, _______,       _______, S(KC_BSLS), MT_DQUO, MT_LBRACE, MT_RBRACE, MT_CLN, S(KC_SCLN),
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      _______, KC_BSLS, S(KC_5), S(KC_8), S(KC_3), S(KC_GRV),                               S(KC_6), S(KC_4), KC_LBRC, KC_RBRC, S(KC_SLSH), S(KC_1),
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,    _______, _______, _______
                                      //`--------------------------------'  `--------------------------------'
  ),

    [NUMS_LAYER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      _______, S(KC_MINS), S(KC_COMM), S(KC_DOT), S(KC_2), ARW_RHT, _______,        _______, _______,    KC_7,    KC_8,    KC_9, S(KC_5), _______,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      _______, MT_SLSH, MT(MOD_LALT, KC_MINS), MT_PLUS, MT(MOD_LSFT, KC_EQL), KC_GRV, _______,        _______, S(KC_4), MT(MOD_RSFT, KC_4), MT(MOD_RCTL, KC_5), MT(MOD_RALT, KC_6), KC_SLSH, S(KC_SCLN),
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      _______, KC_BSLS, S(KC_5), KC_PAST, S(KC_3), S(KC_GRV),                                   KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_COMM,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                           MO(BASE_FN), _______, _______,    _______, _______, MO(BASE_FN)
                                      //`--------------------------------'  `--------------------------------'
  ),

    [FUNCTION_KEYS_LAYER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______, _______,                _______, _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_NUM,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,                _______, _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                  _______,   KC_F1,   KC_F2,   KC_F3, _______,   QUAKE,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,    _______, _______, _______
                                      //`--------------------------------'  `--------------------------------'
  ),

    [MOUSE_LAYER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      KC_ENT, MOD_LGUI, MT(MOD_LALT, KC_LEFT), MT(MOD_LCTL, KC_DOWN), MT(MOD_LSFT, KC_UP), KC_RGHT, KC_ENT,             KC_ENT, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      KC_ESC, KC_TAB, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,                                  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_TAB, KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                               KC_BTN3, KC_BTN2, KC_BTN1,    KC_BTN1, KC_BTN2, KC_BTN3
                                      //`--------------------------------'  `--------------------------------'
  ),

    [BASE_FN] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------,              ,-------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------|              |--------|--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                |--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------------|  |--------------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,    _______, _______, _______
                                      //`--------------------------------'  `--------------------------------'
  ),

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [GAME_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [GAME_NUM_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NAVIGATIONS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [SYMBOLS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NUMS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [FUNCTION_KEYS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [MOUSE_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [BASE_FN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
