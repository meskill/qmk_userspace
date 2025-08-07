#pragma once

#include QMK_KEYBOARD_H

#define KC_RECORD_KEY KC_F15

typedef struct {
    uint16_t tap1;
    uint16_t tap2;
    uint16_t hold;
} tap_dance_tap_hold_t;


void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);

enum {
    // Tap Dance Recording
    TD_RCRD,
};

#define ACTION_TAP_DANCE_TAP_HOLD(tap1, tap2, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, NULL}, .user_data = (void *)&((tap_dance_tap_hold_t){tap1, tap2, hold}), }

