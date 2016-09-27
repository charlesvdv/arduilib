#ifndef _ARDUILIB_IO_H
#define _ARDUILIB_IO_H

// needed for the MODE_* and VALUE_*
#include "../register/reg_pin.h"

int arduilib_set_io_mode(int pin_number, int mode);
int arduilib_get_io_mode(int pin_number);
int arduilib_get_io_value(int pin_number);
int arduilib_set_io_value(int pin_number, int value);

// arduino function definition
void pinMode(int pin, int mode);
int digitalRead(int pin);
void digitalWrite(int pin, int value);

// arduino constant needed for IO
// mode
#define OUTPUT MODE_OUTPUT
#define INPUT MODE_INPUT
// value
#define LOW VALUE_LOW
#define HIGH VALUE_HIGH

// Error code thrown by the IO module
// when we give something different of 0/1 for mode/value
#define ERR_CODE_BAD_IO_VALUE -1
// when the mode is input and we want to set a value
#define ERR_CODE_WRONG_MODE -2
// when the pin has no mode defined
#define ERR_CODE_PIN_UNDEFINED -3

#endif
