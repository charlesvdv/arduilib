#include <stdbool.h>

#include "reg_time.h"

// time in microseconds
static unsigned long time = 0;
// incrementation of the time after each loop
static int incr = 0;

unsigned long reg_get_time() {
    return time;
}

void reg_set_time_interval(int microseconds) {
    incr = microseconds;
}

unsigned long reg_increment_time() {
    if (incr == 0) {
        incr = DEFAULT_INCR_TIME;
    }
    time += incr;
    return time;
}

// Used for testing
void reg_reset_time() {
    time = 0;
    incr = 0;
}
