#ifndef _ARDUILIB_TIME_H
#define _ARDUILIB_TIME_H

unsigned long arduilib_get_time_micros();
unsigned long arduilib_get_time_millis();

void arduilib_delay_micro(unsigned long microseconds);
void arduilib_delay_milli(unsigned long milliseconds);

// define arduino specific function
#define millis() arduilib_get_time_millis()
#define micros() arduilib_get_time_micros()
#define delay(x) arduilib_set_delay_milli(x)
#define delayMicroseconds(x) arduilib_set_delay_micro(x)

#endif
