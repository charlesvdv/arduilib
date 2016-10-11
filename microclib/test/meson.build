test_io = executable('Test IO', 'test_mc_io.c',
                     include_directories: mc_inc,
                     link_with: microclib,
                     dependencies: cmocka_dep,
                     c_args: test_c_args)

test_time = executable('Test time', 'test_mc_time.c',
                     include_directories: mc_inc,
                     link_with: microclib,
                     dependencies: cmocka_dep,
                     c_args: test_c_args)

test_board = executable('Test board', 'test_mc_board.c',
                     include_directories: mc_inc,
                     link_with: microclib,
                     dependencies: cmocka_dep,
                     c_args: test_c_args)

test_event = executable('Test IO event', 'test_mc_io_event.c',
                        include_directories: mc_inc,
                        link_with: microclib,
                        dependencies: cmocka_dep,
                        c_args: test_c_args)

test_int = executable('Test interrupt', 'test_mc_interrupt.c',
                      include_directories: mc_inc,
                      link_with: microclib,
                      dependencies: cmocka_dep,
                      c_args: test_c_args)

test('[microclib] test IO', test_io)
test('[microclib] test time', test_time)
test('[microclib] test board', test_board)
test('[microclib] test IO event', test_event)
test('[microclib] test interrupt', test_int)
