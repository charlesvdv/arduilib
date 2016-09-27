#include <stdio.h>
#include <stdlib.h>

#include "arduilib_logger.h"


void arduilib_handle_error(unsigned long time, char* message, int error_code) {
    arduilib_log_error(time, message, error_code);
    char* data_dump = arduilib_log_dump();
    printf("%s\n", data_dump);
    free(data_dump);
}
