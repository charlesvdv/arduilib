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

int int_jsonify_io_state(int time, mc_io_state *state) {
    json_t *pin_state, *io;
    bool first = false;

    // Convert the io_state into JSON.
    pin_state = json_object();
    json_object_set_new(pin_state, "pin", json_integer(state->pin));
    json_object_set_new(pin_state, "mode", json_integer(state->mode));
    json_object_set_new(pin_state, "value", json_integer(state->value));
    json_object_set_new(pin_state, "forced", json_boolean(state->forced));

    // Test if "io" root JSON object exist.
    io = json_object_get(log, "io");
    if (!json_is_array(io)) {
        // Define the io object at the root of the log data.
        json_t *array = json_array();
        json_object_set(log, "io", array);
        io = json_object_get(log, "io");
        if (!json_is_array(io)) {
            return -1;
        }
        json_decref(array);
        first = true;
    }

    if (json_array_size(io) == 0 && ! first) {
        return -1;
    }

    json_t *time_spec = json_array_get(io, json_array_size(io) - 1);
    json_t *pin_value = json_object_get(time_spec, "value");

    // Check if we already have this time saved.
    if (json_integer_value(json_object_get(time_spec, "time")) != time || first) {
        // Generate a new time value.
        time_spec = json_object();
        json_object_set_new(time_spec, "time", json_integer(time));

        pin_value = json_array();
        json_array_append(pin_value, pin_state);
        json_object_set_new(time_spec, "value", pin_value);

        json_array_append(io, time_spec);
        json_decref(time_spec);
    } else {
        if (! json_is_array(pin_value)) {
            return -1;
        }
        // Check if the pin is already defined and delete
        // the JSON object if it is.
        for (int i = 0; i < json_array_size(pin_value); i++) {
            json_t *data = json_array_get(pin_value, i);
            if (json_integer_value(json_object_get(data, "pin")) == state->pin) {
                json_array_remove(pin_value, i);
                break;
            }
        }

        json_array_append(pin_value, pin_state);
    }
    json_decref(pin_state);
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
