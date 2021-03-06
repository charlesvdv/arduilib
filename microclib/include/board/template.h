#ifndef TEMPLATE_H
#define TEMPLATE_H

/*
 * Warning this header file shoud just be used as a template
 * for OTHER board and not AS a board.
 */

// Digital pins' count is continious and begin by 0.
// This number is inclusive.
#define DIGITAL_PINS_END 0

// Same as digital pins.
#define ANALOG_INPUT_PINS_END 0

// Analog output pins are non-continious.
// Using an array of pins.
static const int ANALOG_OUTPUT_PINS[] = {};
#define ANALOG_OUTPUT_PINS_SIZE sizeof(ANALOG_OUTPUT_PINS) / sizeof(int)

// Same as analog output pins.
static const int DIGITAL_PINS_INTERRUPTS[] = {};
#define DIGITAL_PINS_INTERRUPTS_SIZE sizeof(DIGITAL_PINS_INTERRUPTS) / sizeof(int)

/*
 * Should be set to true for Due, Zero, MKR1000 and 101 board.
 * See https://www.arduino.cc/en/Reference/AttachInterrupt for more details.
 * If true, don't need to set INTERRUPT_PINS.
 */
#define ONE_TO_ONE_MAPPING_PIN_INTERRUPT false

// Same as digital pins.
#define INTERRUPTS_END 0

#endif
