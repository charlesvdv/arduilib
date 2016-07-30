#ifndef _ARDUINO_TIME_H
#define _ARDUINO_TIME_H

unsigned long arduino_lib_get_time_micros();
unsigned long arduino_lib_get_time_millis();

void arduino_lib_delay_micro(unsigned long microseconds);
void arduino_lib_delay_milli(unsigned long milliseconds);

// define arduino specific function
#define millis() arduino_lib_get_time_millis()
#define micros() arduino_lib_get_time_micros()
#define delay(x) arduino_lib_set_delay_milli(x)
#define delayMicroseconds(x) arduino_lib_set_delay_micro(x)

#endif
