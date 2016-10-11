#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "mc_board.h"
#include "mc_error.h"

// Tested with the arduino uno board.

static void test_is_digital() {
    assert_true(mc_is_digital_pin(0));
    assert_true(mc_is_digital_pin(13));

    assert_false(mc_is_digital_pin(-4));
    assert_false(mc_is_digital_pin(14));
}

static void test_is_input_analog() {
    assert_true(mc_is_analog_input_pin(0));
    assert_true(mc_is_analog_input_pin(5));

    assert_false(mc_is_analog_input_pin(-4));
    assert_false(mc_is_analog_input_pin(6));
}

static void test_is_output_analog() {
    assert_true(mc_is_analog_output_pin(5));
    assert_true(mc_is_analog_output_pin(10));

    assert_false(mc_is_analog_output_pin(0));
    assert_false(mc_is_analog_output_pin(7));
}

static void test_is_interrupt() {
    assert_true(mc_is_interrupt(0));
    assert_true(mc_is_interrupt(1));

    assert_false(mc_is_interrupt(-4));
    assert_false(mc_is_interrupt(2));
}

static void test_convert_interrupt() {
    assert_int_equal(mc_convert_interrupt_to_interrupt_pin(0), 2);
    assert_int_equal(mc_convert_interrupt_to_interrupt_pin(1), 3);

    assert_int_equal(mc_convert_interrupt_to_interrupt_pin(2), MC_UNDEFINED_INT);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_is_digital),
        cmocka_unit_test(test_is_input_analog),
        cmocka_unit_test(test_is_output_analog),
        cmocka_unit_test(test_is_interrupt),
        cmocka_unit_test(test_convert_interrupt)
    };

    return cmocka_run_group_tests_name("Board test", tests, NULL, NULL);
}
