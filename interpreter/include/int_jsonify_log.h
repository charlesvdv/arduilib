#ifndef INT_JSONIFY_LOG_H
#define INT_JSONIFY_LOG_H

#include "microclib.h"

void int_jsonifier_init();

int int_log_error(int time, char error_msg[]);

int int_jsonifier_io_states(mc_io_log io_states[], int size);

char* int_get_log();

void int_free_log(char *s);

#endif
