#include <stdio.h>
#include "microclib.h"

#include "ardno_time.h"

static void (*delay_callback)(int);

void ardno_register_delay_callback(void (*callback)(int)) {
    delay_callback = callback; 
}

unsigned long millis() {
    return mc_get_time() / 1000;
}

unsigned long micros() {
    return mc_get_time();
}

void delay(unsigned long millis) {
    delayMicroseconds(millis * 1000); 
}

void delayMicroseconds(unsigned int micros) {
    int start_time = mc_get_time();
    while (mc_get_time() < start_time + micros) {
        // Execute callback and then increment time.
        delay_callback(mc_get_time());
        mc_increment_time();
    }
}
