#ifndef MC_DIGITAL_IO_H
#define MC_DIGITAL_IO_H

#include <stdbool.h>

#define MODE_OUTPUT 0
#define MODE_INPUT 1

#define VALUE_LOW 0
#define VALUE_HIGH 1

struct digital_io_state {
    bool defined;
    bool forced; // true if the value is forced (i.e. without the mode setup)
    int pin;
    int mode;
    int value;
};
typedef struct digital_io_state mc_io_state;

struct digital_io_log {
    int time;
    int states_size;
    mc_io_state *states;
};
typedef struct digital_io_log mc_io_log;

/*
 * Set the pin's mode and initialize the pin.
 */
int mc_set_io_mode(int pin, int mode);

/*
 * Get the pin's mode.
 */
int mc_get_io_mode(int pin, int *mode);

/* 
 * Save the digital value for a given pin. Value should 0 or 1.
 */
int mc_set_digital_io_value(int pin, int value);

/*
 * Force the pin's value (i.e. without setting the pin's mode).
 */
int mc_force_digital_io_value(int pin, int value);

/* 
 * Read the digital value of a given pin. Value pointer should be
 * 0 or 1.
 */
int mc_get_digital_io_value(int pin, int *value);

/*
 * Save the current digital io states.
 */
void mc_save_digital_io_state(int time);

/*
 * Get the size of the current history.
 */
int mc_get_digital_io_history_size();

/*
 * Get all the digital IO history.
 */
void mc_get_digital_io_history(mc_io_log history[], int size);

void mc_free_digital_io_history();

// Functions used only when doing unit testing.
#ifdef UNIT_TEST
/*
 * Get the pins' states data in bulk.
 */
void mc_get_io_dump(mc_io_state states[], int size);

/*
 * Get the size of the array that should be given by
 * mc_get_io_dump function.
 */
int mc_get_io_dump_size();

/*
 * Reset the pin's value and mode to 0 and set defined to false.
 */
void mc_reset_io_states();
#endif

#endif
