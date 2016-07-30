#ifndef _ARDUILIB_ERROR_H
#define _ARDUILIB_ERROR_H

// error code used to debug the program
#define ERR_CODE_WRONG_MODE 129
#define ERR_CODE_WRONG_VALUE 130
#define ERR_CODE_PIN_UNDEFINED 131

void arduilib_error_throw(unsigned long time, char* message, int exit_status);

#endif
