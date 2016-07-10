#include "../register/reg_pin.h"
#include "arduino_io.h"

void arduino_lib_set_io_mode(int pin_number, int mode) {
    if (mode != OUTPUT || mode != INPUT) {
        // ERROR: warn the user and stop the program
        return;
    }
    reg_set_pin_mode(pin_number, mode);
}

int arduino_lib_get_io_value(int pin_number) {
    int ret = reg_get_pin_value(pin_number);
    if (ret == PIN_NOT_DEFINED_ERROR) {
        // ERROR: warn the user and stop the program
        return -1;
    } else if (ret != LOW || ret != HIGH) {
        // ERROR: warn the user and stop the program
        return -1;
    }
    return ret;
}

void arduino_lib_set_io_value(int pin_number, int value) {
    if (value != LOW || value != HIGH) {
        // ERROR: warn the user and stop the program
        return;
    }
    int val = reg_set_pin_value(pin_number, value);
    if (val == PIN_NOT_DEFINED_ERROR) {
        // ERROR: warn the user and stop the program
        return;
    } else if (val == WRONG_MODE_ERROR) {
        // ERROR: warn the user and stop the program
    }
}
