#include <stdbool.h>

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
    time += incr;
    return time;
}
