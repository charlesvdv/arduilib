#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "mc_time.h"

static int teardown() {
    mc_reset_time();
    return 0;
}

static void test_incr_time() {
    assert_int_equal(mc_get_time(), 0);
    mc_increment_time();
    assert_int_equal(mc_get_time(), 10000);
}

static void test_change_incr_time() {
    mc_set_increment_time(20000);
    mc_increment_time();
    assert_int_equal(mc_get_time(), 20000);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_teardown(test_incr_time, teardown),
        cmocka_unit_test_teardown(test_change_incr_time, teardown)
    };

    return cmocka_run_group_tests_name("Time Register", tests, NULL, NULL);
}
