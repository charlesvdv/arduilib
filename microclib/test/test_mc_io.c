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
    if (ret < 0) { return -1; }
    ret = mc_set_io_mode(PIN2, MODE_INPUT);
    if (ret < 0) { return ret; }
    ret = mc_force_digital_io_value(PIN3, VALUE_HIGH);
    return ret;
}

static int setup_get_value() {
    int ret = setup();
    if (ret < 0) { return ret; }
    ret = mc_force_digital_io_value(PIN1, VALUE_HIGH);
    if (ret < 0) { return ret; }
    ret = mc_force_digital_io_value(PIN2, VALUE_LOW);
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

static void test_history() {
    mc_save_digital_io_state(0);
    int size = mc_get_digital_io_history_size();
    assert_int_equal(size, 1);
    mc_io_log history[size];
    mc_get_digital_io_history(history, size);

    assert_int_equal(history[0].time, 0);
    assert_int_equal(history[0].states_size, 3);
    assert_int_equal(history[0].states[0].value, VALUE_HIGH);

    // Test with a second log in the history
    mc_force_digital_io_value(PIN1, VALUE_LOW);
    mc_save_digital_io_state(100);

    size = mc_get_digital_io_history_size();
    assert_int_equal(size, 2);
    mc_io_log history2[size];
    mc_get_digital_io_history(history2, size);

    assert_int_equal(history2[1].time, 100);
    assert_int_equal(history2[1].states_size, 3);
    assert_int_equal(history2[1].states[0].value, VALUE_LOW);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_teardown(test_set_mode, teardown),
        cmocka_unit_test_setup_teardown(test_get_mode, setup, teardown),
        cmocka_unit_test_setup_teardown(test_set_value, setup, teardown),
        cmocka_unit_test_teardown(test_force_value, teardown),
        cmocka_unit_test_setup_teardown(test_get_value, setup_get_value, teardown),
        cmocka_unit_test_setup_teardown(test_history, setup_get_value, teardown)
    };

    return cmocka_run_group_tests_name("Digital IO Arduino Library", tests, NULL, NULL);
}
