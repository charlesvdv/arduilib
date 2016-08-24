#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#include "../reg_time.h"

static int setup() {
    reg_reset_time();

    return 0;
}

static void test_default_incrementation() {
    assert_int_equal(reg_increment_time(), DEFAULT_INCR_TIME);
    assert_int_equal(reg_get_time(), DEFAULT_INCR_TIME);
}

static void test_custom_incrementation() {
    int time_interval = 5;
    reg_set_time_interval(time_interval);
    assert_int_equal(reg_increment_time(), time_interval);
    assert_int_equal(reg_increment_time(), time_interval * 2);
    assert_int_equal(reg_get_time(), time_interval * 2);
}

static void test_reset_time() {
    reg_increment_time();
    reg_reset_time();
    assert_int_equal(reg_get_time(), 0);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(test_default_incrementation, setup),
        cmocka_unit_test_setup(test_custom_incrementation, setup),
        cmocka_unit_test_setup(test_reset_time, setup)
    };

    return cmocka_run_group_tests_name("Time Register", tests, NULL, NULL);
}
