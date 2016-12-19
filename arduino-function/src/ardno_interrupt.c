#include <stdbool.h>

#include "microclib.h"
#include "ardno_error.h"

void attachInterrupt(int interrupt, void (*ISR)(void), int mode) {
    int ret = mc_add_interrupt(interrupt, ISR, mode);
    if (ret < 0) {
        ardno_exit_failure(ret);
    }
}

void detachInterrupt(int interrupt) {
    int ret = mc_remove_interrupt(interrupt);
    if (ret < 0) {
        ardno_exit_failure(ret);
    }
}

void interrupts() {
    mc_change_interrupt_state(true);
}

void noInterrupts() {
    mc_change_interrupt_state(false);
}

int digitalPinToInterrupt(int pin) {
    int ret = mc_convert_interrupt_pin_to_interrupt(pin);
    if (ret < 0) {
        ardno_exit_failure(ret);
    }
    return ret;
}
