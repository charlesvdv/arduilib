#ifndef _ARDUINO_LOGGER_H
#define _ARDUINO_LOGGER_H

#include "../register/reg_pin.h"

void arduino_log_init();
char* arduino_log_dump();

void arduino_log_io(unsigned long time, PinState states[]);
void arduino_log_error(char error[]);

#endif
