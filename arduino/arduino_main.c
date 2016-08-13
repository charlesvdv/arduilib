#include <stdlib.h>
#include <stdio.h>

#include "arduino.h"
#include "arduilib/arduilib_time.h"
#include "register/reg_time.h"
#include "arduilib/arduilib_logger.h"

#define MAX_TIME_RUNNING 500000

int main() {
    arduilib_log_init();
    setup();
    for(; arduilib_get_time_micros() < MAX_TIME_RUNNING; reg_increment_time()) {
        loop();
        PinState* states = reg_dump_pin_data();
        arduilib_log_io(arduilib_get_time_micros(), states, PIN_NUMBER);
        free(states);
    }
    char *s = arduilib_log_dump();
    printf("%s\n", s);
    free(s);
    return EXIT_SUCCESS;
}
