#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdbool.h>

#include "mc_digital_io.h"
#include "mc_error.h"
#include "mc_interrupt.h"

static int isr_value = 0;

void ISR_test() {
    isr_value++;
}

static int setup() {
    int ret = mc_add_interrupt(0, ISR_test, INT_RISING);
    if (ret != MC_SUCCESS) {
        return ret; 
    }
    ret = mc_add_interrupt(1, ISR_test, INT_CHANGE);
    return ret;
}

static int setup2() {
    int ret = mc_add_interrupt(0, ISR_test, INT_FALLING);
    if (ret != MC_SUCCESS) {
        return ret; 
    }
    ret = mc_add_interrupt(1, ISR_test, INT_LOW);
    return ret;
}

static int teardown() {
    mc_change_interrupt_state(true);
    mc_reset_interrupts();
    isr_value = 0;
    return 0;
}

static void test_enable() {
    assert_true(mc_is_interrupt_enabled());
    
    mc_change_interrupt_state(false);
    assert_false(mc_is_interrupt_enabled());
}

static void test_interrupt_remove() {
    assert_int_equal(mc_add_interrupt(0, ISR_test, INT_RISING), MC_SUCCESS);
    assert_int_equal(mc_remove_interrupt(0), MC_SUCCESS);
    assert_int_equal(mc_execute_interrupt(0, 0, 1), MC_NOTHING_TO_DO);
}

static void test_interrupt_execute() {
    assert_int_equal(isr_value, 0);
    assert_int_equal(mc_execute_interrupt(0, VALUE_LOW, VALUE_HIGH), MC_SUCCESS);
    assert_int_equal(isr_value, 1);
    assert_int_equal(mc_execute_interrupt(1, VALUE_HIGH, VALUE_LOW), MC_SUCCESS);
    assert_int_equal(isr_value, 2);
}

static void test_mode1() {
    assert_int_equal(mc_execute_interrupt(0, VALUE_HIGH, VALUE_LOW), MC_NOTHING_TO_DO);
    assert_int_equal(mc_execute_interrupt(1, VALUE_HIGH, VALUE_HIGH), MC_NOTHING_TO_DO);
}

static void test_mode2() {
    assert_int_equal(mc_execute_interrupt(0, VALUE_LOW, VALUE_HIGH), MC_NOTHING_TO_DO);
    assert_int_equal(mc_execute_interrupt(1, VALUE_HIGH, VALUE_HIGH),MC_NOTHING_TO_DO);
}

static void test_undefined_int_num() {
    assert_int_equal(mc_add_interrupt(10, ISR_test, INT_RISING), MC_UNDEFINED_INT);
    assert_int_equal(mc_remove_interrupt(10), MC_UNDEFINED_INT);
    assert_int_equal(mc_remove_interrupt(10), MC_UNDEFINED_INT);
}

static void test_undefined_int() {
    assert_int_equal(mc_execute_interrupt(0, VALUE_LOW, VALUE_HIGH), MC_NOTHING_TO_DO);
}

static void test_int_disabled() {
    // Disable interrupts globally.
    mc_change_interrupt_state(false);

    assert_int_equal(mc_execute_interrupt(0, VALUE_LOW, VALUE_LOW), MC_INT_DISABLED);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_teardown(test_enable, teardown),
        cmocka_unit_test_teardown(test_interrupt_remove, teardown),
        cmocka_unit_test_setup_teardown(test_interrupt_execute, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mode1, setup, teardown),
        cmocka_unit_test_setup_teardown(test_mode2, setup2, teardown),
        cmocka_unit_test(test_undefined_int_num),
        cmocka_unit_test(test_undefined_int),
        cmocka_unit_test(test_int_disabled)
    };

    return cmocka_run_group_tests_name("Interrupt IO", tests, NULL, NULL);
}
