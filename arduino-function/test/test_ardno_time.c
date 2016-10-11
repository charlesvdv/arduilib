#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "microclib.h"
#include "ardno_time.h"

#define UNUSED(x) (void)(x)

static int setup() {
    // Set increment time to 500µs.
    mc_set_increment_time(500);
    return 0;
}

static int teardown() {
    mc_reset_time();
    return 0;
}

static int delay_callback_count = 0;
void test_delay_callback(int time) {
    UNUSED(time); 
    delay_callback_count++;
}

static void test_millis() {
    assert_int_equal(millis(), 0);
    mc_increment_time();
    assert_int_equal(millis(), 0);
    mc_increment_time();
    assert_int_equal(millis(), 1);
}

static void test_delay() {
    assert_int_equal(millis(), 0);
    assert_int_equal(delay_callback_count, 0);

    ardno_register_delay_callback(test_delay_callback);
    delay(1);

    assert_int_equal(micros(), 1000);
    assert_int_equal(delay_callback_count, 2);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_millis, setup, teardown),
        cmocka_unit_test_setup_teardown(test_delay, setup, teardown)
    };

    return cmocka_run_group_tests_name("Arduino time functions", tests, NULL, NULL);
}
