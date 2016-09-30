#include <stdlib.h>
#include <stdio.h>

#include "arduino.h"
#include "arduilib/arduilib_logger.h"
#include "arduilib/arduilib_time.h"
#include "arduilib/arduilib_main.h"

#define MAX_TIME_RUNNING 500000

int main() {
    arduilib_init();
    // Launch the arduino setup() function
    setup();
    for(; arduilib_get_time_micros() <= MAX_TIME_RUNNING; arduilib_increment_time()) {
        arduilib_update_loop();
        // Launch the arduino loop() function
        loop();
    }
    arduilib_exit(EXIT_SUCCESS);
}
