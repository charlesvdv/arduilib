#include <stdio.h>
#include <stdlib.h>

#include "arduilib_logger.h"

#define UNUSED(x) (void)(x)

void arduilib_error_throw(unsigned long time, char* message, int error_code) {
    // error_code is only used when testing to see which error code was generated
    // by the function.
    UNUSED(error_code);

    arduilib_log_error(time, message);
    char* data_dump = arduilib_log_dump();
    printf("%s\n", data_dump);
    free(data_dump);
    exit(EXIT_FAILURE);
}
