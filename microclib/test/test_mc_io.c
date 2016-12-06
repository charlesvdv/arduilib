#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mc_error.h"
#include "mc_digital_io.h"

#define PIN1 1
#define PIN2 2
#define PIN3 3
#define OTHER_PIN 5
#define IMPOSSIBLE_PIN 1000

static int teardown() {
    mc_reset_io_states();
    return 0;
}

// Define PIN1 as an MODE_OUTPUT and PIN2 as an input one.
static int setup() {
    int ret = mc_set_io_mode(PIN1, MODE_OUTPUT);
    ret += mc_set_io_mode(PIN2, MODE_INPUT);
    ret += mc_force_digital_io_value(PIN3, VALUE_HIGH);
    return ret;
}

static int setup_get_value() {
    int ret = setup();
    ret += mc_force_digital_io_value(PIN1, VALUE_HIGH);
    ret += mc_force_digital_io_value(PIN2, VALUE_LOW);
    return ret;
}

static void test_set_mode() {
    assert_int_equal(mc_set_io_mode(PIN1, MODE_OUTPUT), MC_SUCCESS);
    assert_int_equal(mc_set_io_mode(PIN1, MODE_INPUT), MC_SUCCESS);
    assert_int_equal(mc_set_io_mode(PIN2, MODE_OUTPUT), MC_SUCCESS);

    // Verify that we have the right things set.
    int size = mc_get_io_dump_size();
    mc_io_state io_states[size];
    mc_get_io_dump(io_states, size);
    assert_int_equal(io_states[0].mode, MODE_INPUT);
    assert_int_equal(io_states[0].pin, PIN1);
    assert_int_equal(io_states[0].defined, true);
    assert_int_equal(io_states[0].value, 0);
    assert_int_equal(io_states[1].mode, MODE_OUTPUT);

    // Check error returned by the function.
    assert_int_equal(mc_set_io_mode(PIN1, 34), MC_WRONG_MODE);
    assert_int_equal(mc_set_io_mode(IMPOSSIBLE_PIN, MODE_OUTPUT), MC_WRONG_PIN);
}

static void test_get_mode() {
    int mode = 0;
    assert_int_equal(mc_get_io_mode(PIN1, &mode), MC_SUCCESS);
    assert_int_equal(mode, MODE_OUTPUT);
    assert_int_equal(mc_get_io_mode(PIN2, &mode), MC_SUCCESS);
    assert_int_equal(mode, MODE_INPUT);
    assert_int_equal(mc_get_io_mode(PIN3, &mode), MC_PIN_UNDEFINED);

    // Check error returned by the function.
    assert_int_equal(mc_get_io_mode(OTHER_PIN, &mode), MC_PIN_UNDEFINED);
    assert_int_equal(mc_get_io_mode(IMPOSSIBLE_PIN, &mode), MC_WRONG_PIN);
}

static void test_set_value() {
    assert_int_equal(mc_set_digital_io_value(PIN1, VALUE_HIGH), MC_SUCCESS);
    assert_int_equal(mc_set_digital_io_value(PIN3, VALUE_LOW), MC_PIN_UNDEFINED);

    int size = mc_get_io_dump_size();
    mc_io_state io_states[size];
    mc_get_io_dump(io_states, size);

    assert_int_equal(io_states[0].value, VALUE_HIGH);

    // Check error returned by the function.
    assert_int_equal(mc_set_digital_io_value(PIN2, VALUE_LOW), MC_WRONG_PIN_MODE);
    assert_int_equal(mc_set_digital_io_value(IMPOSSIBLE_PIN, VALUE_LOW), MC_WRONG_PIN);
    assert_int_equal(mc_set_digital_io_value(OTHER_PIN, VALUE_LOW), MC_PIN_UNDEFINED);
    assert_int_equal(mc_set_digital_io_value(PIN1, 32), MC_WRONG_VALUE);
}

static void test_force_value() {
    assert_int_equal(mc_force_digital_io_value(PIN1, VALUE_HIGH), MC_SUCCESS);
    assert_int_equal(mc_force_digital_io_value(PIN2, VALUE_LOW), MC_SUCCESS);

    int size = mc_get_io_dump_size();
    mc_io_state io_states[size];
    mc_get_io_dump(io_states, size);

    assert_int_equal(io_states[0].value, VALUE_HIGH);
    assert_true(io_states[0].defined);
    assert_true(io_states[0].forced);
    assert_int_equal(io_states[1].value, VALUE_LOW);

    // Check error returned by the function.
    assert_int_equal(mc_force_digital_io_value(PIN1, 32), MC_WRONG_VALUE);
    assert_int_equal(mc_force_digital_io_value(IMPOSSIBLE_PIN, VALUE_LOW), MC_WRONG_PIN);
}

static void test_get_value() {
    int value = 0;
    assert_int_equal(mc_get_digital_io_value(PIN1, &value), MC_SUCCESS);
    assert_int_equal(value, VALUE_HIGH);

    assert_int_equal(mc_get_digital_io_value(PIN2, &value), MC_SUCCESS);
    assert_int_equal(value, VALUE_LOW);

    assert_int_equal(mc_get_digital_io_value(PIN3, &value), MC_FORCED_VALUE);
    assert_int_equal(value, VALUE_HIGH);

    // Check error returned by the function.
    assert_int_equal(mc_get_digital_io_value(IMPOSSIBLE_PIN, &value), MC_WRONG_PIN);
    assert_int_equal(mc_get_digital_io_value(OTHER_PIN, &value), MC_PIN_UNDEFINED);
}

int handle_basic_history(int time, mc_io_state *state) {
    if (time != 0) {
        return EXIT_FAILURE;
    }
    if ((state->pin == PIN1 && state->value == VALUE_HIGH) ||
            (state->pin == PIN2 && state->value == VALUE_LOW) ||
            (state->pin == PIN3 && state->value == VALUE_HIGH)) {
        return EXIT_SUCCESS;
    }
    else {
        return EXIT_FAILURE;
    }
}

static void test_save_history() {
    mc_save_digital_io_state(0);
    assert_int_equal(mc_handle_history(0, handle_basic_history), MC_SUCCESS);

    mc_free_digital_io_history();
}

int handle_reset_changed(int time, mc_io_state *state) {
    if (time == 1) {
        // We should not have this time logged as we didn't change any value.
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static void test_reset_changed_history() {
    mc_save_digital_io_state(0);

    // Recall the same function.
    test_get_value();

    mc_save_digital_io_state(1);
    assert_int_equal(mc_handle_history(1, handle_reset_changed), MC_SUCCESS);

    mc_free_digital_io_history();
}

int handle_failure(int time, mc_io_state *state) {
    return -1;
}

static void test_empty_history() {
    assert_int_equal(mc_handle_history(0, handle_failure), MC_SUCCESS);
}

static void test_handle_function_failure() {
    mc_save_digital_io_state(0);

    assert_int_equal(mc_handle_history(0, handle_failure), MC_CALLBACK_ERR);

    mc_free_digital_io_history();
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_teardown(test_set_mode, teardown),
        cmocka_unit_test_setup_teardown(test_get_mode, setup, teardown),
        cmocka_unit_test_setup_teardown(test_set_value, setup, teardown),
        cmocka_unit_test_teardown(test_force_value, teardown),
        cmocka_unit_test_setup_teardown(test_get_value, setup_get_value, teardown),
        cmocka_unit_test_setup_teardown(test_save_history, setup_get_value, teardown),
        cmocka_unit_test_setup_teardown(test_reset_changed_history, setup_get_value, teardown),
        cmocka_unit_test(test_empty_history),
        cmocka_unit_test_setup_teardown(test_handle_function_failure, setup_get_value, teardown)
    };

    return cmocka_run_group_tests_name("Digital IO Arduino Library", tests, NULL, NULL);
}
