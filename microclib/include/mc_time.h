#ifndef MC_TIME_H
#define MC_TIME_H

/*
 * Return the current time in microseconds.
 */
int mc_get_time();

/*
 * Return the previous time. If time = 0, return 0.
 */
int mc_calculate_previous_time(int new_time);

/*
 * Increment the current time with the incremental time set
 * by "mc_set_increment_time" or 1ms by default.
 */
void mc_increment_time();

/*
 * Set the default incremental time. Default is 1ms.
 * Increment time must be in microseconds.
 */
int mc_set_increment_time(int incr_time);

#ifdef UNIT_TEST
void mc_reset_time();
#endif

#endif
