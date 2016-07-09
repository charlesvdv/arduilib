#ifndef _ARDUINO_IO_H
#define _ARDUINO_IO_H

// needed for the MODE_* and VALUE_*
#include "../register/reg_pin.h"

void arduino_lib_set_io_mode(int pin_number, int mode);
int arduino_lib_get_io_value(int pin_number);
void arduino_lib_set_io_value(int pin_number, int value);

// arduino constant needed for IO
// mode
#define OUTPUT MODE_OUTPUT
#define INPUT MODE_INPUT
// value
#define LOW VALUE_LOW
#define HIGH VALUE_HIGH

// arduino specific function
#define pinMode(x, y) arduino_lib_set_io_mode(x, y)
#define digitalWrite(x, y) arduino_lib_set_io_value(x, y)
#define digitalRead(x) arduino_lib_get_io_value(x)

#endif
