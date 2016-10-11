#ifndef MC_BOARD_H
#define MC_BOARD_H

#include <stdbool.h>

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

#ifdef BOARD_UNO
#include "board/uno.h"
#endif

#endif
