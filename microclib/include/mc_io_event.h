#ifndef MC_IO_EVENT_H
#define MC_IO_EVENT_H

struct io_event_data {
    int time;
    int pin;
    int value;
};
typedef struct io_event_data mc_io_event_data;

/*
 * Add an IO event in the registery.
 */
int mc_add_io_event(int time, int pin, int value);

int mc_get_io_events_size(int time1, int time2);

/*
 * Get all the IO events for a given time.
 */
int mc_get_io_events(int time1, int time2, mc_io_event_data io_ev[], int size);

#ifdef UNIT_TEST
void mc_reset_io_events();
#endif

#endif
