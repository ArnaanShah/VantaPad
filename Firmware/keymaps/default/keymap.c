// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {
    REOPEN_TAB = SAFE_RANGE,
    AUTO_CLICKER,
    KC_CYCLE_LAYERS
};

enum layer_names {
    _BASE,
    _LAYER1,
    _LAYER2
};

#define LAYER_CYCLE_START 0
#define LAYER_CYCLE_END   2

//  Auto Clicker 
static bool     auto_clicker_active = false;
static uint32_t auto_clicker_timer  = 0;
#define AUTO_CLICK_INTERVAL_MS 20


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case REOPEN_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT("t")));
            }
            return false;
        case AUTO_CLICKER:
            if (record->event.pressed) {
                auto_clicker_active = !auto_clicker_active;
                auto_clicker_timer  = timer_read32();
            }
            return false;
        case KC_CYCLE_LAYERS:
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t next_layer = (current_layer >= LAYER_CYCLE_END) ? LAYER_CYCLE_START : current_layer + 1;
                layer_move(next_layer);
            }
            return false;
    }
    return true;
}

// Autoclicker tick
void housekeeping_task_user(void) {
    if (auto_clicker_active && timer_elapsed32(auto_clicker_timer) >= AUTO_CLICK_INTERVAL_MS) {
        auto_clicker_timer = timer_read32();
        tap_code(MS_BTN1);
    }
}

// RGB initialization
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 255, 100); // red
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2); // speed 2
    
    wait_ms(2500); // delay before startup
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAYER1] = { ENCODER_CCW_CW(LCTL(KC_PGUP), LCTL(KC_PGDN)) },
    [_LAYER2] = { ENCODER_CCW_CW(LCTL(KC_Z), LCTL(KC_Y)) },
};
#endif

// OLED 
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0; 
}

bool oled_task_user(void) {

    oled_write_P(PSTR("Arnaan Shah"), false);

    return false;
}
#endif

// Layoit
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE, // Top row + Encoder Button
        REOPEN_TAB, AUTO_CLICKER, KC_CYCLE_LAYERS
    ),
    [_LAYER1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_LAYER2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    )
};