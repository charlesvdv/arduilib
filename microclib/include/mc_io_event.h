#ifndef MC_IO_EVENT_H
#define MC_IO_EVENT_H

/*
 * Add an IO event in the registery.
 */
int mc_add_io_event(int time, int pin, int value);


/*
 * Execute the event handler when we are in the time between time1 (exclusive) and
 * time2 (inclusive).
 */
int mc_execute_io_events(int time1, int time2, int (*handle_event)(int, int));

#ifdef UNIT_TEST
void mc_reset_io_events();
#endif

#endif
