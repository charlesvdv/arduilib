ardno_src = ['ardno_time.c',
             'ardno_digital_io.c', 
             'ardno_interrupt.c',
             'ardno_error.c']

arduino_lib = static_library('arduino',
                          ardno_src,
                          include_directories: [mc_inc, ardno_inc],
                          link_with: microclib)
