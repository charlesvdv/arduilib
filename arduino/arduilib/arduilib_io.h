#ifndef _ARDUILIB_IO_H
#define _ARDUILIB_IO_H

// needed for the MODE_* and VALUE_*
#include "../register/reg_pin.h"

void arduilib_set_io_mode(int pin_number, int mode);
int arduilib_get_io_value(int pin_number);
void arduilib_set_io_value(int pin_number, int value);

// arduino constant needed for IO
// mode
#define OUTPUT MODE_OUTPUT
#define INPUT MODE_INPUT
// value
#define LOW VALUE_LOW
#define HIGH VALUE_HIGH

// arduino specific function
#define pinMode(x, y) arduilib_set_io_mode(x, y)
#define digitalWrite(x, y) arduilib_set_io_value(x, y)
#define digitalRead(x) arduilib_get_io_value(x)

#endif
