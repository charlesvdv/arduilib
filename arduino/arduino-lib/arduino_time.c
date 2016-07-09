#include "../register/reg_time.h"

unsigned long arduino_lib_get_time_micros() {
    return reg_get_time();
}

unsigned long arduino_lib_get_time_millis() {
    return reg_get_time() / 1000;
}

void arduino_lib_delay_micro(unsigned long microseconds) {
    unsigned long start_time = reg_get_time();
    while(start_time + microseconds <= reg_increment_time()) { }
}

void arduino_lib_delay_milli(unsigned long milliseconds) {
    arduino_lib_delay_micro(milliseconds * 1000);
}
