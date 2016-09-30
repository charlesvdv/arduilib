#include <stdlib.h>

#include "arduilib_logger.h"
#include "arduilib_main.h"
#include "../register/reg_time.h"
#include "../register/reg_pin.h"

unsigned long arduilib_get_time_micros() {
    return reg_get_time();
}

unsigned long arduilib_get_time_millis() {
    return reg_get_time() / 1000;
}

void arduilib_delay_micro(unsigned long microseconds) {
    unsigned long start_time = reg_get_time();
    while(reg_increment_time() <= start_time + microseconds) {
        arduilib_update_loop();
    }
}

void arduilib_delay_milli(unsigned long milliseconds) {
    arduilib_delay_micro(milliseconds * 1000);
}

void arduilib_increment_time() {
    reg_increment_time();
}
