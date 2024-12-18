/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#define QUICK_TAP_TERM_PER_KEY

#define AUTO_SHIFT_TIMEOUT 160
#define RETRO_SHIFT 300
#define AUTO_SHIFT_REPEAT
#define NO_AUTO_SHIFT_NUMERIC

#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT
#define LEADER_TIMEOUT 200

#define COMBO_TERM 30
#define COMBO_STRICT_TIMER
#define COMBO_ONLY_FROM_LAYER 0

#define TAPPING_TERM 175 // TAP VS HOLD timing in milliseconds
// Pick good defaults for enabling home row mods
#define TAP_CODE_DELAY 5
#define TAP_HOLD_CAPS_DELAY 0
#define PERMISSIVE_HOLD

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 12
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 3
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 32

// See https://docs.qmk.fm/features/rgb_matrix#rgb-matrix-effects
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_JELLYBEAN_RAINDROPS
#define RGB_MATRIX_DEFAULT_HUE 148 // Default color ‘azure’ blue from https://docs.qmk.fm/features/rgblight.

//#define USE_MATRIX_I2C

//#define QUICK_TAP_TERM 0
//#define TAPPING_TERM 100

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
