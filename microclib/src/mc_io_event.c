#include <string.h>

#include "mc_board.h"
#include "mc_digital_io.h"
#include "mc_error.h"
#include "mc_io_event.h"

#define MAX_IO_EVENTS 50

static mc_io_event_data io_events[MAX_IO_EVENTS];
static int io_events_pos = 0;

int mc_add_io_event(int time, int pin, int value) {
    if (! mc_is_digital_pin(pin)) { return MC_WRONG_PIN; }
    if (value != VALUE_LOW && value != VALUE_HIGH) { return MC_WRONG_VALUE; }

    io_events[io_events_pos++] = (mc_io_event_data) {
        .time = time,
        .pin = pin,
        .value = value
    };
    return MC_SUCCESS;
}

int mc_get_io_events(int time1, int time2, mc_io_event_data io_ev[], int size) {   
    int count = 0;
    for (int i = 0; i <= io_events_pos; i++) {
        if (time1 <= io_events[i].time && io_events[i].time <= time2) {
            memcpy(&io_ev[count++], &io_events[i], sizeof(mc_io_event_data));
        }
        if (count + 1 == size) {
            return MC_SUCCESS; 
        }
    }
    return MC_SUCCESS;
}

int mc_get_io_events_size(int time1, int time2) {
    int count = 0;
    for (int i = 0; i <= io_events_pos; i++) {
        if (time1 <= io_events[i].time && io_events[i].time <= time2) {
            count++; 
        } 
    }
    return count;
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
