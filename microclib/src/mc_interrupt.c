#include <stdbool.h>
#include <stddef.h>

#include "mc_board.h"
#include "mc_digital_io.h"
#include "mc_error.h"
#include "mc_interrupt.h"

#define INTERRUPT_MAX_SIZE INTERRUPTS_END + 1

struct int_store {
    bool defined;
    int pin;
    void (*ISR)(void);
    mc_interrupt_mode mode;
};
struct int_store interrupts[INTERRUPT_MAX_SIZE];

static bool interrupt_enabled = true;

bool mc_is_interrupt_enabled() {

    return interrupt_enabled;
}

void mc_change_interrupt_state(bool enabled) {
    interrupt_enabled = enabled;
}

int mc_add_interrupt(int interrupt, void (*ISR)(void), mc_interrupt_mode mode) {
    if (! mc_is_interrupt(interrupt)) {
        return MC_UNDEFINED_INT;
    }
    int pin = mc_convert_interrupt_to_interrupt_pin(interrupt);
    if (pin == MC_UNDEFINED_INT) {
        return MC_UNDEFINED_INT; 
    }
    interrupts[interrupt] = (struct int_store) {
        .defined = true,
        .pin = pin,
        .ISR = ISR,
        .mode = mode
    };
    return MC_SUCCESS;
}

int mc_remove_interrupt(int interrupt) {
    if (! mc_is_interrupt(interrupt)) {
        return MC_UNDEFINED_INT; 
    }
    interrupts[interrupt] = (struct int_store) {
        .defined = false,
        .pin = 0,
        .ISR = NULL,
        .mode = 0
    };
    return MC_SUCCESS;
}

int mc_execute_interrupt(int interrupt, int past_value, int current_value) {
    if (! interrupt_enabled) { return MC_INT_DISABLED; }
    if (! mc_is_interrupt(interrupt)) { return MC_UNDEFINED_INT; }
    if (! interrupts[interrupt].defined) { return MC_NOTHING_TO_DO; }

    // Return if mode is not valid.
    struct int_store inter = interrupts[interrupt];
    if (inter.mode == INT_CHANGE && past_value == current_value) {
        return MC_NOTHING_TO_DO; 
    } if (inter.mode == INT_FALLING && past_value < current_value) {
        return MC_NOTHING_TO_DO; 
    } if (inter.mode == INT_RISING && past_value > current_value) {
        return MC_NOTHING_TO_DO; 
    } if (inter.mode == INT_LOW && current_value == VALUE_HIGH) {
        return MC_NOTHING_TO_DO; 
    }
    #if defined(BOARD_DUE) || defined(BOARD_ZERO) || defined(BOARD_MKR1000)
    if (inter.mode == INT_HIGH && current_value == VALUE_LOW) {
        return MC_NOTHING_TO_DO; 
    }
    #endif

    // Execute the ISR.
    void (*isr)(void) = interrupts[interrupt].ISR;
    isr();
    return MC_SUCCESS;
}

void mc_reset_interrupts() {
    for (int i = 0; i < INTERRUPT_MAX_SIZE; i++) {
        mc_remove_interrupt(i);
    }
}
