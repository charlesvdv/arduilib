#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#include "../arduilib_io.h"
#include "../../register/reg_pin.h"

#define PIN 1

static void test_bad_io_value() {
    // Don't need this, we are just forced by cmocka when we have a mock.
    will_return(__wrap_arduilib_get_time_millis, 0);
    will_return(__wrap_arduilib_get_time_millis, 0);

    assert_int_equal(arduilib_set_io_mode(PIN, 34), ERR_CODE_BAD_IO_VALUE);
    assert_int_equal(arduilib_set_io_value(PIN, 34), ERR_CODE_BAD_IO_VALUE);
}

static void test_pin_not_defined() {
    will_return(__wrap_arduilib_get_time_millis, 0);
    will_return(__wrap_arduilib_get_time_millis, 0);
    will_return(__wrap_arduilib_get_time_millis, 0);
    will_return(__wrap_reg_get_pin_mode, PIN_NOT_DEFINED_ERROR);
    will_return(__wrap_reg_get_pin_value, PIN_NOT_DEFINED_ERROR);
    will_return(__wrap_reg_set_pin_value, PIN_NOT_DEFINED_ERROR);

    assert_int_equal(arduilib_get_io_mode(PIN), ERR_CODE_PIN_UNDEFINED);
    assert_int_equal(arduilib_get_io_value(PIN), ERR_CODE_PIN_UNDEFINED);
    assert_int_equal(arduilib_set_io_value(PIN, HIGH), ERR_CODE_PIN_UNDEFINED);
}

static void test_wrong_mode() {
    will_return(__wrap_arduilib_get_time_millis, 0);
    will_return(__wrap_reg_set_pin_value, WRONG_MODE_ERROR);

    assert_int_equal(arduilib_set_io_value(PIN, HIGH), ERR_CODE_WRONG_MODE);
}

static void test_get_value_mode() {
    will_return(__wrap_reg_get_pin_mode, MODE_OUTPUT);
    will_return(__wrap_reg_get_pin_value, VALUE_HIGH);

    assert_int_equal(arduilib_get_io_mode(PIN), OUTPUT);
    assert_int_equal(arduilib_get_io_value(PIN), HIGH);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_bad_io_value),
        cmocka_unit_test(test_pin_not_defined),
        cmocka_unit_test(test_wrong_mode),
        cmocka_unit_test(test_get_value_mode)
    };

    return cmocka_run_group_tests_name("IO Arduino Library", tests, NULL, NULL);
}
