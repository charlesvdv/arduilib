#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "reg_pin.h"

#define IS_PIN_DEFINED(pn) states[pn].defined

static PinState states[PIN_NUMBER];

void initialize_pin(int pin_number, int mode, int value) {
    states[pin_number] = (PinState) {
        .defined = true,
        .mode = mode,
        .value = value
    };
}

int reg_get_pin_mode(int pin_number) {
    if (! IS_PIN_DEFINED(pin_number)) { return PIN_NOT_DEFINED_ERROR; }
    return states[pin_number].mode;
}

void reg_set_pin_mode(int pin_number, int mode) {
    if (! IS_PIN_DEFINED(pin_number)) { 
        initialize_pin(pin_number, mode, VALUE_LOW);
        return;
    } 
    states[pin_number].mode = mode;
} 

int reg_get_pin_value(int pin_number) {
    if (! IS_PIN_DEFINED(pin_number)) { return PIN_NOT_DEFINED_ERROR; }
    return states[pin_number].value;
}

int reg_set_pin_value(int pin_number, int value) {
    if (! IS_PIN_DEFINED(pin_number)) { return PIN_NOT_DEFINED_ERROR; }
    if (states[pin_number].mode != MODE_OUTPUT) { return WRONG_MODE_ERROR; }
    states[pin_number].value = value;
    return SUCCESS;
}

