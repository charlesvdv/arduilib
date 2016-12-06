#ifndef MC_ERROR_H
#define MC_ERROR_H

#include <limits.h>

#define MC_MAX_ERR_MSG_SIZE 200

#define MC_ERROR \
    X(MC_WRONG_VALUE, "The value is an impossible one. The value should be LOW or HIGH (0 or 1).") \
    X(MC_WRONG_MODE, "The mode is an impossible value. The mode should be OUTPUT or INPUT (0 or 1).") \
    X(MC_WRONG_PIN_MODE, "The pin you are trying to write on is read only because the mode is INPUT.") \
    X(MC_WRONG_PIN, "The pin you are trying to access is not existing.") \
    X(MC_PIN_UNDEFINED, "The pin is not configured correctly. Try to set his mode first.") \
    X(MC_FORCED_VALUE, "This pin has a forced value by an external event. Try to configure it before accessing it.") \
    X(MC_WRONG_INCR_TIME_VALUE, "The incrementation time is not correct.") \
    X(MC_FORBIDDEN_INCR_TIME_CHANGE, "It isn't possible to change the incrementation time while the program is running.") \
    X(MC_UNDEFINED_INT, "The interrupt code is impossible.") \
    X(MC_CALLBACK_ERR, "A callback error occured while running the code.")

// Error code is always < 0.
// Information code is always > 0.
enum mc_err {
    // Information code.
    MC_SUCCESS = 0,
    MC_NOTHING_TO_DO,
    MC_INT_DISABLED,
    MC_HISTORY_NOT_COMPLETE,

    USELESS = SHRT_MIN, // This entry is just used to put all the error code in negative number.
    // Error code.
    #define X(a, b) a,
    MC_ERROR
    #undef X
};
typedef enum mc_err mc_error;

void mc_get_error_msg(int error_code, char *msg);

#endif
