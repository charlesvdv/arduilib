#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "reg_pin.h"

#define IS_PIN_DEFINED(pn) states[pn].defined

static PinState states[PIN_NUMBER];

void initialize_pin(int pin_number, Mode mode, Value value) {
    states[pin_number] = (PinState) {
        .defined = true,
        .mode = mode,
        .value = value
    };
}

Mode reg_get_pin_mode(int pin_number) {
    if (! IS_PIN_DEFINED(pin_number)) { /* ERROR */ }
    return states[pin_number].mode;
}

void reg_set_pin_mode(int pin_number, Mode mode) {
    if (! IS_PIN_DEFINED(pin_number)) { 
        initialize_pin(pin_number, mode, VALUE_LOW);
        return;
    } 
    states[pin_number].mode = mode;
} 

Value reg_get_pin_value(int pin_number) {
    if (! IS_PIN_DEFINED(pin_number)) { /* ERROR */ }
    return states[pin_number].value;
}

void reg_set_pin_value(int pin_number, Value value) {
    if (! IS_PIN_DEFINED(pin_number)) { /* ERROR */ }
    if (states[pin_number].mode != MODE_OUTPUT) { /* ERROR */ }
    states[pin_number].value = value;
}

