#include <check.h>

#include "reg_pin.h"
#include "test_reg.h"

START_TEST(test_pin_mode)
{
    reg_set_pin_mode(1, MODE_INPUT);
    ck_assert_int_eq(reg_get_pin_mode(1), MODE_INPUT);
}
END_TEST

START_TEST(test_pin_not_defined)
{
    ck_assert_int_eq(reg_get_pin_mode(1), PIN_NOT_DEFINED_ERROR);
    ck_assert_int_eq(reg_get_pin_value(1), PIN_NOT_DEFINED_ERROR);
    ck_assert_int_eq(reg_set_pin_value(1, VALUE_HIGH), PIN_NOT_DEFINED_ERROR);
}
END_TEST

START_TEST(test_pin_value_output)
{
    reg_set_pin_mode(1, MODE_OUTPUT);
    reg_set_pin_value(1, VALUE_HIGH);
    ck_assert_int_eq(reg_get_pin_value(1), VALUE_HIGH);
}
END_TEST

START_TEST(test_pin_value_input)
{
    reg_set_pin_mode(1, MODE_INPUT);
    ck_assert_int_eq(reg_get_pin_value(1), VALUE_LOW);
}
END_TEST

START_TEST(test_pin_mode_in_set_value)
{
    reg_set_pin_mode(1, MODE_INPUT);
    ck_assert_int_eq(reg_set_pin_value(1, VALUE_HIGH), WRONG_MODE_ERROR);
}
END_TEST

START_TEST(test_pin_dump)
{
    reg_set_pin_mode(1, MODE_INPUT);
    reg_set_pin_mode(2, MODE_OUTPUT);
    reg_set_pin_value(2, VALUE_HIGH);
    PinState* states = reg_dump_pin_data();
    ck_assert_int_eq(states[1].mode, MODE_INPUT);
    ck_assert_int_eq(states[2].mode, MODE_OUTPUT);
    ck_assert_int_eq(states[2].value, VALUE_HIGH);
}
END_TEST


Suite* make_reg_pin_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Pin register");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_pin_mode);
    tcase_add_test(tc_core, test_pin_not_defined);
    tcase_add_test(tc_core, test_pin_value_input);
    tcase_add_test(tc_core, test_pin_value_output);
    tcase_add_test(tc_core, test_pin_mode_in_set_value);
    tcase_add_test(tc_core, test_pin_dump);
    suite_add_tcase(s, tc_core);

    return s;
}
