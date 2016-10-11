#ifndef ARDNO_ERROR_H
#define ARDNO_ERROR_H

void ardno_register_exit_failure_callback(void (*callbck)(int, char*));

void ardno_exit_failure(int error_code);

#endif
