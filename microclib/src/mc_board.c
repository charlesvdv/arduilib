#include "mc_board.h"
#include "mc_error.h"

bool mc_is_in_array(int value, const int array[], int size) {
    for (int i=0; i < size; i++) {
        if (value == array[i]) {
            return true; 
        } 
    }
    return false;
}

bool mc_is_digital_pin(int pin) {
    return (0 <= pin && pin <= DIGITAL_PINS_END);
}

bool mc_is_analog_input_pin(int pin) {
    return (0 <= pin && pin <= ANALOG_INPUT_PINS_END);
}

bool mc_is_analog_output_pin(int pin) {
    return mc_is_in_array(pin, ANALOG_OUTPUT_PINS, ANALOG_OUTPUT_PINS_SIZE);
}

bool mc_is_interrupt(int interrupt) {
    if (ONE_TO_ONE_MAPPING_PIN_INTERRUPT) {
        return mc_is_in_array(interrupt, DIGITAL_PINS_INTERRUPTS, 
                DIGITAL_PINS_INTERRUPTS_SIZE); 
    }
    return (0 <= interrupt && interrupt <= INTERRUPTS_END);
}

int mc_convert_interrupt_to_interrupt_pin(int interrupt) {
    if (! mc_is_interrupt(interrupt)) {
        return MC_UNDEFINED_INT;
    }
    if (ONE_TO_ONE_MAPPING_PIN_INTERRUPT) {
        return interrupt;
    }
    return DIGITAL_PINS_INTERRUPTS[interrupt];
}
