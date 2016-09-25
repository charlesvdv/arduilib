#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#define UNUSED(x) (void)(x)

void __wrap_arduilib_handle_error(unsigned long time, char* message, int error_code) {
    UNUSED(time); UNUSED(message); UNUSED(error_code);
    // Do nothing.
}
