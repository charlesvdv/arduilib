#include <stdbool.h>

// time in microseconds
static int time = 0;
// incrementation of the time after each loop
static int incr = 0;

int reg_get_time() {
    return time;
}

void reg_set_time_interval(int microseconds) {
    incr = microseconds;
}

int reg_increment_time() {
    time += incr;
    return time;
}
