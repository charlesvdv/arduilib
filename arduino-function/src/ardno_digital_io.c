#include "microclib.h"

#include "ardno_error.h"

void pinMode(int pin, int mode) {
    int ret = mc_set_io_mode(pin, mode);
    if (ret < 0) {
        ardno_exit_failure(ret);
    }
}

int digitalRead(int pin) {
    int value = -1;
    int ret = mc_get_digital_io_value(pin, &value);
    if (ret < 0) {
        ardno_exit_failure(ret);
    }
    return value;
}

void digitalWrite(int pin, int value) {
    int ret = mc_set_digital_io_value(pin, value);
    if (ret < 0) {
        ardno_exit_failure(ret);
    }
}
