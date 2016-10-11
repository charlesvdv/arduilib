#include "mc_time.h"
#include "mc_error.h"

// 10 millis
#define DEFAULT_INCR_TIME 10000

static int time = 0;
static int incr_time = DEFAULT_INCR_TIME;

int mc_get_time() {
    return time;
}

int mc_calculate_previous_time(int new_time) {
    if (new_time - incr_time < 0) { return 0; }
    return new_time - incr_time;
}

void mc_increment_time() {
    time += incr_time;
}

int mc_set_increment_time(int new_incr_time) {
    if (time != 0) {
        return MC_FORBIDDEN_INCR_TIME_CHANGE;
    }
    if (new_incr_time <= 0) {
        return MC_WRONG_INCR_TIME_VALUE;
    }
    incr_time = new_incr_time;
    return MC_SUCCESS;
}

// ********** Unit-testing specifics **********  

void mc_reset_time() {
    time = 0;
    incr_time = DEFAULT_INCR_TIME;
}
