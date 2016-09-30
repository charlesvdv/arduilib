#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../register/reg_pin.h"

#define MAX_FMT_SIZE 300

static json_t *array;

void arduilib_log_init() {
    array = json_array();
    if (!array) {
        fprintf(stderr, "Unable to create the json array.\n");
        // We will not exit with arduilib_exit because the JSON
        // is not created.
        exit(EXIT_FAILURE);
    }
}

char* arduilib_log_dump() {
    char *s = json_dumps(array, 0);
    // free the memory of the JSON array
    json_decref(array);
    return s;
}

void arduilib_log_io(unsigned long time, PinState states[], int pin_number) {
    json_t *root, *pin_data;
    root = json_object();
    json_object_set_new(root, "type", json_string("io"));
    json_object_set_new(root, "time", json_integer(time));

    // fill pin_data
    pin_data = json_array();
    for (int i = 1; i < pin_number; i++) {
        if (! states[i].defined) { continue; }
        json_t *pin = json_object();
        json_object_set_new(pin, "pin", json_integer(i));
        json_object_set_new(pin, "value", json_integer(states[i].value));
        json_object_set_new(pin, "mode", json_integer(states[i].mode));

        json_array_append(pin_data, pin);
        // free the json_object as the json_array_append make a copy
        // of this object.
        json_decref(pin);
    }

    json_object_set_new(root, "data", pin_data);
    json_array_append(array, root);
    // free the json_object as the json_array_append make a copy
    // of this object.
    json_decref(root);
}

void arduilib_log_error(unsigned long time, int error_code, char *fmt, ...) {
    // Format the error message
    char formatted_message[MAX_FMT_SIZE];
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(formatted_message, MAX_FMT_SIZE, fmt, argptr);
    va_end(argptr);

    json_t *object = json_object();
    json_object_set_new(object, "type", json_string("error"));
    json_object_set_new(object, "message", json_string(formatted_message));
    json_object_set_new(object, "time", json_integer(time));
    json_object_set_new(object, "code", json_integer(error_code));
    json_array_append_new(array, object);
}
