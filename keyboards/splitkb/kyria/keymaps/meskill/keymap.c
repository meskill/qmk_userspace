/* Copyright 2023 meskill (https://github.com/meskill)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "features/lang_word.h"
#include "features/process_lang_word.h"
#include "features/lang_switch.h"
#include "macro.h"
#include "chords.c"
#include "mod_tap.h"
#include "mod_hold.h"
#include "layout.c"
#include "override.c"
#include "rgb.h"

// Disable power led on controller
void keyboard_pre_init_user(void) {
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
    writePinHigh(24);
}

void keyboard_post_init_user(void) {
    keyboard_post_init_rgb();
}

void matrix_scan_user(void) {
    lang_word_task();
    lang_switch_task();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (
        !process_lang_switch(keycode, record) ||
        !process_mod_tap(keycode, record) ||
        !process_mod_hold(keycode, record) ||
        !process_macro(keycode, record) ||
        !process_lang_word(keycode, record)
    ) {
        return false;
    }

    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT_LSHIFT);  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        case RU_BE:
        case RU_YU:
        case RU_HA:
        case RU_HARD:
        case RU_ZHE:
        case RU_YO:
        case RU_E:
            if (IS_LAYER_ON(RU)) {
                add_weak_mods(MOD_BIT_LSHIFT);
                return true;
            }

            return false;
        case SEND_I:
        case SEND_THE:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool lang_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_LSFT:
        case KC_RSFT:
        case S_SLH:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return true;
        case SEND_I:
        case SEND_THE:
            return true;
    }

    switch (QK_MODS_GET_BASIC_KEYCODE(keycode)) {
        // Keycodes that continue Lang Word
        case KC_A ... KC_Z:
        case KC_MINS ... KC_SLASH:
        case KC_1 ... KC_0:
        case KC_LEFT:
        case KC_RIGHT:
            return true;
    }

    return false;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LALT_T(KC_LBRC):
        case LCTL_T(KC_LPRN):
        case LSFT_T(S_LCBR):
        case LGUI_T(S_RCBR):
        case LT(NAV, KC_RPRN):
        case LT(SYM, S_RBRC):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    post_process_lang_word(keycode, record);
    post_process_record_rgb(keycode, record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint16_t layer = get_highest_layer(state);
    bool is_ru = layer_state_cmp(state, RU);
    bool is_ru_prev = IS_LAYER_ON(RU);

    if (is_ru_prev && !is_ru) {
        SWTC_EN();
    } else if (is_ru) {
        if (layer == SYM || layer == GAME) {
            SWTC_EN();
        } else {
            SWTC_RU();
        }
    }

    layer_state_set_rgb(state);

    return state;
}

void housekeeping_task_user(void) {
    housekeeping_task_rgb();
}

void suspend_wakeup_init_user(void) {
    layer_move(0);
    SWTC_EN();
}
