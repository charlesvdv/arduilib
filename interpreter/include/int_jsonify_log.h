#ifndef INT_JSONIFY_LOG_H
#define INT_JSONIFY_LOG_H

#include "microclib.h"

void int_jsonifier_init();

int int_log_error(int time, char error_msg[]);

int int_jsonify_io_state(int time, mc_io_state *state);

char* int_get_log();

void int_free_log(char *s);

#endif
