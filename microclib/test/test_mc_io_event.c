#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "mc_digital_io.h"
#include "mc_error.h"
#include "mc_io_event.h"

static int teardown() {
    mc_reset_io_events();
    return 0;
}

static void test_io_events() {
    assert_int_equal(mc_add_io_event(50, 4, VALUE_HIGH), MC_SUCCESS);
    assert_int_equal(mc_add_io_event(100, 5, VALUE_LOW), MC_SUCCESS);
    assert_int_equal(mc_add_io_event(100, 4, VALUE_LOW), MC_SUCCESS);

    assert_int_equal(mc_add_io_event(150, 45, VALUE_LOW), MC_WRONG_PIN);
    assert_int_equal(mc_add_io_event(150, 4, 42), MC_WRONG_VALUE);

    assert_int_equal(mc_get_io_events_size(50, 75), 1);
    assert_int_equal(mc_get_io_events_size(100, 125), 2);
    assert_int_equal(mc_get_io_events_size(50, 100), 3);

    mc_io_event_data io_events[2];
    mc_get_io_events(100, 125, io_events, 2);
    assert_int_equal(io_events[0].time, 100);
    assert_int_equal(io_events[0].pin, 5);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_teardown(test_io_events, teardown)
    };

    return cmocka_run_group_tests_name("IO events test", tests, NULL, NULL);
}
