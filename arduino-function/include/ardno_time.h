#ifndef ARDNO_TIME_H
#define ARDNO_TIME_H

void ardno_register_delay_callback(void (*callback)(int));

unsigned long millis();

unsigned long micros();

void delay(unsigned long millis);

void delayMicroseconds(unsigned int micros);

#endif
