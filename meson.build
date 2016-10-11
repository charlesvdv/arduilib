project('arduinint', 'c', default_options: ['c_std=c11'])

test_c_args = '-DUNIT_TEST'

cmocka_dep = dependency('cmocka')

subdir('microclib')
subdir('arduino-function')
subdir('interpreter')
