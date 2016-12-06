#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mc_error.h"
#include "mc_digital_io.h"
#include "mc_board.h"

#define MAX_HISTORY_ENTRY 3000

static mc_io_state dig_io_states[DIGITAL_PINS_END + 1];

static mc_io_log dig_io_history[MAX_HISTORY_ENTRY];
static int history_pos = 0;

// ********** Get/Set value/mode **********

int mc_set_io_mode(int pin, int mode) {
    // Sanity check.
    if (mode != MODE_INPUT && mode != MODE_OUTPUT) {
        return MC_WRONG_MODE;
    }
    if (! mc_is_digital_pin(pin)) {
        return MC_WRONG_PIN;
    }

    int offset = 0;
    for (; dig_io_states[offset].defined; offset++) {
        // Check if the pin is not already defined.
        if (dig_io_states[offset].pin == pin) {
            if (dig_io_states[offset].mode != mode) {
                dig_io_states[offset].changed = true;
            }
            dig_io_states[offset].mode = mode;
            // Reset value to 0 as the pin is not giving any voltage.
            dig_io_states[offset].value = 0;
            return MC_SUCCESS;
        }
    }
    dig_io_states[offset] = (mc_io_state) {
        .defined = true,
        .forced = false,
        .changed = true,
        .pin = pin,
        .mode = mode,
        .value = 0
    };
    return MC_SUCCESS;
}

int mc_get_io_mode(int pin, int *mode) {
    if (! mc_is_digital_pin(pin)) {
        return MC_WRONG_PIN;
    }
    for (int i = 0; dig_io_states[i].defined; i++) {
        if (dig_io_states[i].pin == pin && !dig_io_states[i].forced) {
            *mode = dig_io_states[i].mode;
            return MC_SUCCESS;
        }
    }
    return MC_PIN_UNDEFINED;
}

int mc_set_digital_io_value(int pin, int value) {
    if (value != VALUE_LOW && value != VALUE_HIGH) {
        return MC_WRONG_VALUE;
    }
    if (! mc_is_digital_pin(pin)) {
        return MC_WRONG_PIN;
    }
    for (int i = 0; dig_io_states[i].defined; i++) {
        if (dig_io_states[i].pin == pin && !dig_io_states[i].forced) {
            if (dig_io_states[i].mode != MODE_OUTPUT) {
                return MC_WRONG_PIN_MODE;
            }

            if (dig_io_states[i].value != value) {
                dig_io_states[i].changed = true;
            }
            dig_io_states[i].value = value;
            return MC_SUCCESS;
        }
    }
    return MC_PIN_UNDEFINED;
}

int mc_force_digital_io_value(int pin, int value) {
    if (value != VALUE_LOW && value != VALUE_HIGH) {
        return MC_WRONG_VALUE;
    }
    if (! mc_is_digital_pin(pin)) {
        return MC_WRONG_PIN;
    }
    int offset = 0;
    for (; dig_io_states[offset].defined; offset++) {
        if (dig_io_states[offset].pin == pin) {
            if (dig_io_states[offset].value != value) {
                dig_io_states[offset].changed = true;
            }
            dig_io_states[offset].value = value;
            return MC_SUCCESS;
        }
    }
    // If not defined, create it.
    dig_io_states[offset] = (mc_io_state) {
        .defined = true,
        .forced = true,
        .changed = true,
        .pin = pin,
        .value = value,
        .mode = -1
    };
    return MC_SUCCESS;
}

int mc_get_digital_io_value(int pin, int *value) {
    if (! mc_is_digital_pin(pin)) {
        return MC_WRONG_PIN;
    }
    for (int i = 0; dig_io_states[i].defined; i++) {
        if (dig_io_states[i].pin == pin) {
            *value = dig_io_states[i].value;
            if (dig_io_states[i].forced) { return MC_FORCED_VALUE; }
            return MC_SUCCESS;
        }
    }
    return MC_PIN_UNDEFINED;
}

// ********** Unit-testing specifics **********

int mc_get_io_dump_size() {
    int size = 0;
    for (; dig_io_states[size].defined; size++) {}
    return size;
}

void mc_get_io_dump(mc_io_state states[], int size) {
    for (int i = 0; i < size; i++) {
        memcpy(&states[i], &dig_io_states[i], sizeof(mc_io_state));
    }
}

void mc_reset_io_states() {
    history_pos = 0;

    for (int i = 0; dig_io_states[i].defined; i++) {
        dig_io_states[i] = (mc_io_state) {
            .defined = false,
            .forced = false,
            .changed = false,
            .pin = 0,
            .value = 0,
            .mode = 0
        };
    }
}

// ********** Handle digital io history **********

int mc_handle_history(int max_time, int (*handle_history)(int, mc_io_state*)) {
    for (int i = 0; i < history_pos; i++) {
        if (dig_io_history[i].time > max_time) {
            return MC_HISTORY_NOT_COMPLETE;
        }
        for (int j = 0; dig_io_history[i].states[j] != NULL; j++) {
            mc_io_state *state = dig_io_history[i].states[j];
            if (handle_history(dig_io_history[i].time, state) != MC_SUCCESS) {
                return MC_CALLBACK_ERR;
            }
        }
    }
    return MC_SUCCESS;
}

void mc_save_digital_io_state(int time) {
    int count = 0;
    mc_io_state **states = malloc((DIGITAL_PINS_END+1) * sizeof(mc_io_state *));

    for (int i = 0; i <= DIGITAL_PINS_END; i++) {
        if (! dig_io_states[i].changed || ! dig_io_states[i].defined) { continue; }
        states[count] = malloc(sizeof(mc_io_state));
        memcpy(states[count++], &dig_io_states[i], sizeof(mc_io_state));
        dig_io_states[i].changed = false;
    }
    if (count == 0) {
        free(states);
        return;
    }

    states = realloc(states, (count + 1) * sizeof(mc_io_state *));
    states[count] = NULL;
    dig_io_history[history_pos++] = (mc_io_log) {
        .time = time,
        .states = states
    };
}

void mc_free_digital_io_history() {
    for (int i = 0; i < history_pos; i++) {
        for (int j = 0; dig_io_history[i].states[j] != NULL; j++) {
            free(dig_io_history[i].states[j]);
        }
        free(dig_io_history[i].states);
    }
}
