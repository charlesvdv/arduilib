#ifndef MC_BOARD_H
#define MC_BOARD_H

#include <stdbool.h>

#ifdef BOARD_UNO
#include "board/uno.h"
#else
#error This board is not defined.
#endif


/*
 * Test if the pin is a possible option.
 */
bool mc_is_digital_pin(int pin);
bool mc_is_analog_input_pin(int pin);
bool mc_is_analog_output_pin(int pin);

/*
 * Check if the interrupt number is correct.
 */
bool mc_is_interrupt(int interrupt);

/*
 * Translate the interrupt number to his right digital pin.
 */
int mc_convert_interrupt_to_interrupt_pin(int interrupt);

/*
 * Translate the pin into the right interupt number.
 */
int mc_convert_interrupt_pin_to_interrupt(int pin);

#endif
