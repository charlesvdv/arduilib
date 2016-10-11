#ifndef MC_INTERRUPT_H
#define MC_INTERRUPT_H

#include <stdbool.h>

#include "mc_digital_io.h"

enum int_mode {
    // HACK but it's the easiest solution I see.
#if defined(BOARD_DUE) || defined(BOARD_ZERO) || defined(BOARD_MKR1000)
    // With arduino, the int_high and the value_high are both defined as 
    // HIGH we thus need them to be equals.
    INT_HIGH = VALUE_HIGH,
#endif
    INT_LOW = VALUE_LOW, 
    INT_CHANGE,
    INT_RISING,
    INT_FALLING
};
typedef enum int_mode mc_interrupt_mode;

bool mc_is_interrupt_enabled();

void mc_change_interrupt_state(bool enabled);

int mc_add_interrupt(int interrupt, void (*ISR)(void), mc_interrupt_mode mode);

int mc_remove_interrupt(int interrupt);

int mc_execute_interrupt(int interrupt, int past_value, int current_value);

#ifdef UNIT_TEST
void mc_reset_interrupts();
#endif

#endif
