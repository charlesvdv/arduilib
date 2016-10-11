int_src = ['int_jsonify_log.c',
           'int_arduino_code.c',
           'int_main.c']

int_exec = executable('interpreter',
                      int_src,
                      include_directories: [int_inc, mc_inc, ardno_inc],
                      dependencies: jansson_dep,
                      link_with: [microclib, arduino_lib])
