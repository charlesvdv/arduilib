#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
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

    if (dig_io_states[pin].defined) {
        if (dig_io_states[pin].mode != mode) {
            dig_io_states[pin].changed = true;
            dig_io_states[pin].mode = mode;
        }
        // Reset value to 0 as the pin is not giving any voltage.
        dig_io_states[pin].value = 0;
        return MC_SUCCESS;
    }

    dig_io_states[pin] = (mc_io_state) {
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
    if (! dig_io_states[pin].defined) {
        return MC_PIN_UNDEFINED;
    }
    *mode = dig_io_states[pin].mode;
    return MC_SUCCESS;
}

int mc_set_digital_io_value(int pin, int value) {
    if (value != VALUE_LOW && value != VALUE_HIGH) {
        return MC_WRONG_VALUE;
    }
    if (! mc_is_digital_pin(pin)) {
        return MC_WRONG_PIN;
    }
    if (! dig_io_states[pin].defined) {
        return MC_PIN_UNDEFINED;
    }
    if (dig_io_states[pin].mode != MODE_OUTPUT) {
        return MC_WRONG_PIN_MODE;
    }
    if (dig_io_states[pin].value != value) {
        dig_io_states[pin].changed = true;
        dig_io_states[pin].value = value;
        dig_io_states[pin].forced = false;
    }
    return MC_SUCCESS;
}

int mc_force_digital_io_value(int pin, int value) {
    if (value != VALUE_LOW && value != VALUE_HIGH) {
        return MC_WRONG_VALUE;
    }
    if (! mc_is_digital_pin(pin)) {
        return MC_WRONG_PIN;
    }
    if (dig_io_states[pin].defined) {
        if (dig_io_states[pin].value != value) {
            dig_io_states[pin].changed = true;
            dig_io_states[pin].value = value;
        }
        return MC_SUCCESS;
    }
    // If not defined, create it.
    dig_io_states[pin] = (mc_io_state) {
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
    if (! dig_io_states[pin].defined) {
        return MC_PIN_UNDEFINED;
    }
    *value = dig_io_states[pin].value;
    if (dig_io_states[pin].forced) { return MC_FORCED_VALUE; }
    return MC_SUCCESS;
}

// ********** Unit-testing specifics **********

void mc_get_io_dump(mc_io_state states[], int size) {
    for (int i = 0; i < size; i++) {
        memcpy(&states[i], &dig_io_states[i], sizeof(mc_io_state));
    }
}

void mc_reset_io_states() {
    history_pos = 0;
    for (int i = 0; i <= DIGITAL_PINS_END; i++) {
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
