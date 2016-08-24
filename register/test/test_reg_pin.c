#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdlib.h>

#include "../reg_pin.h"

#define pin 1

static int setup() {
    reg_reset_pins();

    return 0;
}

static void test_pin_mode() {
    reg_set_pin_mode(pin, MODE_INPUT);
    assert_int_equal(reg_get_pin_mode(pin), MODE_INPUT);
}

static void test_pin_value_output() {
    // setup
    reg_set_pin_mode(pin, MODE_OUTPUT);

    int ret = reg_set_pin_value(pin, VALUE_HIGH);
    assert_int_equal(ret, SUCCESS);
    assert_int_equal(reg_get_pin_value(pin), VALUE_HIGH);
}

static void test_default_pin_value_mode_input() {
    // setup
    reg_set_pin_mode(pin, MODE_INPUT);

    int val = reg_get_pin_value(pin);
    assert_int_equal(val, VALUE_LOW);
}

static void test_reset_pins() {
    // setup
    reg_set_pin_mode(pin, MODE_OUTPUT);
    reg_set_pin_value(pin, VALUE_HIGH);

    reg_reset_pins();

    assert_int_equal(reg_get_pin_value(pin), PIN_NOT_DEFINED_ERROR);
}

static void test_pin_not_defined() {
    assert_int_equal(reg_get_pin_value(pin), PIN_NOT_DEFINED_ERROR);
    assert_int_equal(reg_set_pin_value(pin, VALUE_LOW), PIN_NOT_DEFINED_ERROR);
    assert_int_equal(reg_get_pin_mode(pin), PIN_NOT_DEFINED_ERROR);
}

static void test_wrong_mode() {
    // setup
    reg_set_pin_mode(pin, MODE_INPUT);

    int val = reg_set_pin_value(pin, VALUE_HIGH);
    assert_int_equal(val, WRONG_MODE_ERROR);
    assert_int_equal(reg_get_pin_value(pin), VALUE_LOW);
}

static void test_dump_states() {
    int pin2 = 49;
    // setup
    reg_set_pin_mode(pin, MODE_INPUT);
    reg_set_pin_mode(pin2, MODE_OUTPUT);
    reg_set_pin_value(pin2, VALUE_HIGH);

    PinState *states = reg_dump_pin_data();
    assert_int_equal(states[pin].mode, MODE_INPUT);
    assert_int_equal(states[pin2].value, VALUE_HIGH);
    assert_int_equal(states[34].defined, false);
    free(states);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(test_pin_mode, setup),
        cmocka_unit_test_setup(test_pin_value_output, setup),
        cmocka_unit_test_setup(test_default_pin_value_mode_input, setup),
        cmocka_unit_test_setup(test_reset_pins, setup),
        cmocka_unit_test_setup(test_pin_not_defined, setup),
        cmocka_unit_test_setup(test_wrong_mode, setup),
        cmocka_unit_test_setup(test_dump_states, setup)
    };

    return cmocka_run_group_tests_name("Pin Register", tests, NULL, NULL);
}
