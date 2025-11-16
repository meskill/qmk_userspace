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

#include "lang_switch.h"
#include "debug.h"

bool process_lang_switch(uint16_t keycode, keyrecord_t *record) {
    bool down = record->event.pressed;
    int mods = get_mods() | get_oneshot_mods();

    uint16_t lang_layer_keycode = keymap_key_to_keycode(LANG_SWITCH_LAYER, record->event.key);

    if (keycode != lang_layer_keycode || !mods || mods & MOD_MASK_SHIFT) {
        return true;
    }

    uint16_t zero_layer_keycode = keymap_key_to_keycode(0, record->event.key);

    if (keycode != zero_layer_keycode) {
        if (down) {
            register_code(zero_layer_keycode);
        } else {
            unregister_code(zero_layer_keycode);
        }

        return false;
    }

    return true;
}
