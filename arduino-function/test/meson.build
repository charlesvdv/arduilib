test_time = executable('Test arduino time', 'test_ardno_time.c',
                     include_directories: [mc_inc, ardno_inc],
                     link_with: [arduino_lib, microclib],
                     dependencies: cmocka_dep,
                     c_args: test_c_args)

test('[arduino-function] Test time', test_time)
