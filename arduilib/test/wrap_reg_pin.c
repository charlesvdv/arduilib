#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#define UNUSED(x) (void)(x)

int __wrap_reg_get_pin_mode(int pin_number) {
    UNUSED(pin_number);

    return (int) mock();
}

void __wrap_reg_set_pin_mode(int pin_number, int mode) {
    UNUSED(pin_number); UNUSED(mode);
    // Do nothing.
}

int __wrap_reg_get_pin_value(int pin_number) {
    UNUSED(pin_number);

    return (int) mock();
}

int __wrap_reg_set_pin_value(int pin_number, int value) {
    UNUSED(pin_number); UNUSED(value);

    return (int) mock();
}
