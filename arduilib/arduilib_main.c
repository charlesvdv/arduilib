#include <stdio.h>
#include <stdlib.h>

#include "arduilib_io.h"
#include "arduilib_time.h"
#include "arduilib_logger.h"

void arduilib_init() {
    arduilib_log_init();
}

void arduilib_update_loop() {
    // Log io data
    PinState *states = reg_dump_pin_data();
    arduilib_log_io(arduilib_get_time_millis(), states, PIN_NUMBER);
    free(states);
}

void arduilib_exit(int code) {
    // Dump the JSON
    char* data_dump = arduilib_log_dump();
    printf("%s\n", data_dump);
    free(data_dump);

    // exit with or without success
    exit(code);
}
