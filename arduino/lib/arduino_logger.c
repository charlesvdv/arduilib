#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

#include "../register/reg_pin.h"

static json_t *array;

void arduino_log_init() {
    array = json_array();
    if (!array) {
        fprintf(stderr, "Unable to create the json array.");
        exit(EXIT_FAILURE);
    }
}

char* arduino_log_dump() {
    char *s = json_dumps(array, 0);
    puts(s);
    // free the memory of the JSON array
    json_decref(array);
}

void arduino_log_io(unsigned long time, PinState states[], int pin_number) {
    json_t *root, *pin_data;
    root = json_object();
    json_object_set_new(root, "type", json_string("io"));
    json_object_set_new(root, "time", json_integer(time));

    // fill pin_data
    pin_data = json_array();
    for (int i = 0; i < pin_number; i++) {
        if (! states[i].defined) { continue; }
        json_t *pin = json_object();
        json_object_set_new(pin, "pin", json_integer(i));
        json_object_set_new(pin, "value", json_integer(states[i].value));
        json_object_set_new(pin, "mode", json_integer(states[i].mode));

        json_array_append(pin_data, pin);
    }

    json_object_set_new(root, "data", pin_data);
    json_array_append(array, root);
}

void arduino_log_error(unsigned long time, char *error) {
    json_t *object = json_object();
    json_object_set_new(object, "type", json_string("error"));
    json_object_set_new(object, "message", json_string(error));
    json_object_set_new(object, "time", json_integer(time));
    json_array_append_new(array, object);
}
