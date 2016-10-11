#include <string.h>

#include "mc_error.h"


#define X(a, b) b,
char *mc_error_msg[] = {
    MC_ERROR
};
#undef X

void mc_get_error_msg(int error_code, char* msg) {
    if (error_code >= 0) {
        strcpy(msg, "Success.");
    } else {
        int offset = error_code - SHRT_MIN - 1;
        strncpy(msg, mc_error_msg[offset], MC_MAX_ERR_MSG_SIZE); 
    }
}
