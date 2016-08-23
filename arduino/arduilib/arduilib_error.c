#include <stdio.h>
#include <stdlib.h>

#include "arduilib_logger.h"

void arduilib_error_throw(unsigned long time, char* message, int exit_status) {
    arduilib_log_error(time, message);
    char* data_dump = arduilib_log_dump();
    printf("%s\n", data_dump);
    free(data_dump);
    exit(exit_status);
}
