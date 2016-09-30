#include <stdio.h>
#include <stdlib.h>

#include "../register/reg_pin.h"

#include "arduilib_io.h"
#include "arduilib_logger.h"
#include "arduilib_time.h"
#include "arduilib_main.h"

#define ERR_MSG_SIZE 200

#define ERR_BAD_IO_VALUE "The pin %i's IO value (i.e. the mode or the pin's value) " \
                         "should be %i or %i not %i"
#define ERR_WRONG_MODE_DEFINED "The pin %i's mode is not defined as an output"
#define ERR_PIN_UNDEFINED "The pin %i is undefined. Try to set the mode first"

int arduilib_set_io_mode(int pin_number, int mode) {
    if (mode != OUTPUT && mode != INPUT) {
        arduilib_log_error(arduilib_get_time_millis(), ERR_CODE_BAD_IO_VALUE,
                ERR_BAD_IO_VALUE, pin_number, OUTPUT, INPUT, mode);
        return ERR_CODE_BAD_IO_VALUE;
    }
    reg_set_pin_mode(pin_number, mode);
    return 0;
}

int arduilib_get_io_mode(int pin_number) {
    int mode = reg_get_pin_mode(pin_number);
    if (mode == PIN_NOT_DEFINED_ERROR) {
        arduilib_log_error(arduilib_get_time_millis(), ERR_CODE_PIN_UNDEFINED,
                ERR_PIN_UNDEFINED, pin_number);
        return ERR_CODE_PIN_UNDEFINED;
    }
    return mode;
}

int arduilib_get_io_value(int pin_number) {
    int ret = reg_get_pin_value(pin_number);
    if (ret == PIN_NOT_DEFINED_ERROR) {
        arduilib_log_error(arduilib_get_time_millis(), ERR_CODE_PIN_UNDEFINED,
                ERR_PIN_UNDEFINED, pin_number);
        return ERR_CODE_PIN_UNDEFINED;
    }
    if (ret != LOW && ret != HIGH) {
        arduilib_log_error(arduilib_get_time_millis(), ERR_CODE_BAD_IO_VALUE,
                ERR_BAD_IO_VALUE, pin_number, LOW, HIGH, ret);
        return ERR_CODE_BAD_IO_VALUE;
    }
    return ret;
}

int arduilib_set_io_value(int pin_number, int value) {
    if (value != LOW && value != HIGH) {
        arduilib_log_error(arduilib_get_time_millis(), ERR_CODE_BAD_IO_VALUE,
                ERR_BAD_IO_VALUE, pin_number, OUTPUT, INPUT, value);
        return ERR_CODE_BAD_IO_VALUE;
    }
    int val = reg_set_pin_value(pin_number, value);
    if (val == PIN_NOT_DEFINED_ERROR) {
        arduilib_log_error(arduilib_get_time_millis(), ERR_CODE_PIN_UNDEFINED,
                ERR_PIN_UNDEFINED, pin_number);
        return ERR_CODE_PIN_UNDEFINED;
    }
    if (val == WRONG_MODE_ERROR) {
        arduilib_log_error(arduilib_get_time_millis(), ERR_CODE_WRONG_MODE,
                ERR_WRONG_MODE_DEFINED, pin_number);
        return ERR_CODE_WRONG_MODE;
    }
    return 0;
}

// --- Arduino function definition ---

void pinMode(int pin, int mode) {
    int ret = arduilib_set_io_mode(pin, mode);
    if (ret < 0) {
        arduilib_exit(EXIT_FAILURE);
    }
}

int digitalRead(int pin) {
    int ret = arduilib_get_io_value(pin);
    if (ret < 0) {
        arduilib_exit(EXIT_FAILURE);
    }
    return ret;
}

void digitalWrite(int pin, int value) {
    int ret = arduilib_set_io_value(pin, value);
    if (ret < 0) {
        arduilib_exit(EXIT_FAILURE);
    }
}
