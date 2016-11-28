#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "mc_digital_io.h"
#include "mc_error.h"
#include "mc_io_event.h"

static int pin = -1;
static int value = -1;
static int count = 0;

int handle_event_fail(int pin, int value) {
    // Error.
    return -3;
}

int handle_event(int p, int v) {
    pin = p;
    value = v;
    return 0;
}

int handle_event_count(int p, int v) {
    handle_event(p, v);
    count++;
    return 0;
}

static int teardown() {
    mc_reset_io_events();
    pin = -1;
    value = -1;
    count = 0;
    return 0;
}

static int setup() {
    int status = mc_add_io_event(0, 1, VALUE_HIGH);
    status += mc_add_io_event(50, 1, VALUE_LOW);
    status += mc_add_io_event(150, 0, VALUE_HIGH);
    status += mc_add_io_event(200, 2, VALUE_LOW);
    return status;
}

static void test_set_io_events() {
    assert_int_equal(mc_add_io_event(0, 10, VALUE_HIGH), MC_SUCCESS);
    assert_int_equal(mc_add_io_event(50, 4, VALUE_HIGH), MC_SUCCESS);
    assert_int_equal(mc_add_io_event(100, 5, VALUE_LOW), MC_SUCCESS);
    assert_int_equal(mc_add_io_event(100, 4, VALUE_LOW), MC_SUCCESS);

    assert_int_equal(mc_add_io_event(150, 45, VALUE_LOW), MC_WRONG_PIN);
    assert_int_equal(mc_add_io_event(150, 4, 42), MC_WRONG_VALUE);
}

static void test_execute_io_events() {
    mc_execute_io_events(49, 50, handle_event);
    assert_int_equal(pin, 1);
    assert_int_equal(value, VALUE_LOW);
}

static void test_inclusive_execute_io_events() {
    // Test inclusive time1 value.
    mc_execute_io_events(50, 100, handle_event);
    assert_int_equal(pin, -1);
    assert_int_equal(value, -1);
}

static void test_first_time_execute_io_events() {
    // Test 0, 0 values
    mc_execute_io_events(0, 0, handle_event);
    assert_int_equal(pin, 1);
    assert_int_equal(value, VALUE_HIGH);
}

static void test_multiple_execute_io_events() {
    mc_execute_io_events(49, 150, handle_event_count);
    assert_int_equal(count, 2);
    assert_int_equal(pin, 0);
    assert_int_equal(value, VALUE_HIGH);
}

static void test_execute_fail_io_events() {
    assert_int_equal(mc_execute_io_events(10, 12, handle_event_fail), MC_SUCCESS);

    assert_int_equal(mc_execute_io_events(49, 50, handle_event_fail), MC_CALLBACK_ERR);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_teardown(test_set_io_events, teardown),
        cmocka_unit_test_setup_teardown(test_execute_io_events, setup, teardown),
        cmocka_unit_test_setup_teardown(test_inclusive_execute_io_events, setup, teardown),
        cmocka_unit_test_setup_teardown(test_first_time_execute_io_events, setup, teardown),
        cmocka_unit_test_setup_teardown(test_multiple_execute_io_events, setup, teardown),
        cmocka_unit_test_setup_teardown(test_execute_fail_io_events, setup, teardown)
    };

    return cmocka_run_group_tests_name("IO events test", tests, NULL, NULL);
}
