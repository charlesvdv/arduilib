#ifndef _ARDUILIB_LOGGER_H
#define _ARDUILIB_LOGGER_H

#include "../register/reg_pin.h"

void arduilib_log_init();
char* arduilib_log_dump();

void arduilib_log_io(unsigned long time, PinState states[], int pin_number);
void arduilib_log_error(unsigned long time, int error_code, char* error, ...);

#endif
