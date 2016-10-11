#include <stdlib.h>

#include "microclib.h"

static void (*exit_failure_callback)(int, char*);

void ardno_register_exit_failure_callback(void (*callbck)(int, char*)) {
    exit_failure_callback = callbck; 
}

void ardno_exit_failure(int error_code) {
    char error_msg[200];
    mc_get_error_msg(error_code, error_msg);

    int time = mc_get_time();
    exit_failure_callback(time, error_msg);
}
