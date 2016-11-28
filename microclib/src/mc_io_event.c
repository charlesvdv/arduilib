#include <string.h>

#include "mc_board.h"
#include "mc_digital_io.h"
#include "mc_error.h"
#include "mc_io_event.h"

#define MAX_IO_EVENTS 50

struct io_event_data {
    int time;
    int pin;
    int value;
};
typedef struct io_event_data mc_io_event_data;

static mc_io_event_data io_events[MAX_IO_EVENTS];
static int io_events_pos = -1;

int mc_add_io_event(int time, int pin, int value) {
    if (! mc_is_digital_pin(pin)) { return MC_WRONG_PIN; }
    if (value != VALUE_LOW && value != VALUE_HIGH) { return MC_WRONG_VALUE; }

    io_events[++io_events_pos] = (mc_io_event_data) {
        .time = time,
        .pin = pin,
        .value = value
    };
    return MC_SUCCESS;
}

int mc_execute_io_events(int time1, int time2, int (*handle_event)(int, int)) {
    for (int i = 0; i <= io_events_pos; i++) {
        if ((time2 == 0 || time1 < io_events[i].time) && io_events[i].time <= time2) {
            if (handle_event(io_events[i].pin, io_events[i].value) != MC_SUCCESS) {
                return MC_CALLBACK_ERR;
            }
        }
    }
    return MC_SUCCESS;
}

void mc_reset_io_events() {
    for (int i = 0; i <= io_events_pos; i++) {
        io_events[i] = (mc_io_event_data) {
            .time = 0,
            .pin = 0,
            .value = 0
        };
    }
    io_events_pos = 0;
}
