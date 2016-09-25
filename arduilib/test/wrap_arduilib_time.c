#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#define UNUSED(x) (void)(x)

unsigned long __wrap_arduilib_get_time_micros() {
    return (unsigned long) mock();
}

unsigned long __wrap_arduilib_get_time_millis() {
    return (unsigned long) mock();
}

void __wrap_arduilib_delay_micro(unsigned long microseconds) {
    UNUSED(microseconds);
    // Do nothing.
}

void __wrap_arduilib_delay_milli(unsigned long milliseconds) {
    UNUSED(milliseconds);
    // Do nothing.
}

void __wrap_arduilib_increment_time() {
    // Do nothing.
}
