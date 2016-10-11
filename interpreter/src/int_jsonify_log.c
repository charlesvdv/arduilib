#include <stdio.h>
#include <jansson.h>

#include "int_jsonify_log.h"

static json_t *log;

void int_jsonifier_init() {
    log = json_object();
    if (!log) {
        fprintf(stderr, "Unable to initialize the logger.");
        exit(EXIT_FAILURE);
    }
}

int int_log_error(int time, char error_msg[]) {
    json_t *error = json_object();
    json_object_set_new(error, "time", json_integer(time));
    json_object_set_new(error, "msg", json_string(error_msg));

    json_object_set(log, "error", error);
    json_decref(error);
    return 0;
}

int int_jsonifier_io_states(mc_io_log io_states[], int size) {
    json_t *states_root = json_array();
    for (int i = 0; i < size; i++) {
        mc_io_state *temp_states = io_states[i].states;

        json_t *states_log = json_array();
        for (int j = 0; j < io_states[i].states_size; j++) {
            json_t *pin_state_log = json_object(); 
            json_object_set_new(pin_state_log, "pin", json_integer(temp_states[j].pin));
            json_object_set_new(pin_state_log, "mode", json_integer(temp_states[j].mode));
            json_object_set_new(pin_state_log, "value", json_integer(temp_states[j].value));
            json_object_set_new(pin_state_log, "forced", json_boolean(temp_states[j].forced));

            json_array_append(states_log, pin_state_log);
            json_decref(pin_state_log);
        }
        
        json_t *states_info_log = json_object();
        json_object_set_new(states_info_log, "time", json_integer(io_states[i].time));
        json_object_set_new(states_info_log, "value", states_log);

        json_array_append(states_root, states_info_log);

        json_decref(states_info_log);
    }
    json_object_set_new(log, "io", states_root);

    return 0;
}

char* int_get_log() {
    char *s = json_dumps(log, 0);
    json_decref(log);
    return s;
}

void int_free_log(char* s) {
    free(s);
}
