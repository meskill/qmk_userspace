#include "tap_dance.h"

tap_dance_action_t tap_dance_actions[] = {
    [TD_RCRD] = ACTION_TAP_DANCE_TAP_HOLD(LALT(KC_RECORD_KEY), LCA(KC_RECORD_KEY), MEH(KC_RECORD_KEY)),
};

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (
        state->pressed
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
    ) {
            tap_code16(tap_hold->hold);
    } else {
        if (state->count >= 2) {
            tap_code16(tap_hold->tap2);
        } else {
            tap_code16(tap_hold->tap1);
        }
    }
}
