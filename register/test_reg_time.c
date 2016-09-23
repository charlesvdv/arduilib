#include <check.h>

#include "reg_time.h"
#include "test_reg.h"

START_TEST(test_default_increment_time)
{
    ck_assert_int_eq(reg_get_time(), 0);
    ck_assert_int_eq(reg_increment_time(), DEFAULT_INCR_TIME);
    ck_assert_int_eq(reg_get_time(), DEFAULT_INCR_TIME);
}
END_TEST

START_TEST(test_set_increment_time)
{
    ck_assert_int_eq(reg_get_time(), 0);
    reg_set_time_interval(5);
    ck_assert_int_eq(reg_increment_time(), 5);
}
END_TEST

Suite* make_reg_time_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Time register");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_default_increment_time);
    tcase_add_test(tc_core, test_set_increment_time);
    suite_add_tcase(s, tc_core);

    return s;
}
