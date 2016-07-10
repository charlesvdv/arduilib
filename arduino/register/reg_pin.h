#ifndef _REG_PIN_H
#define _REG_PIN_H

#define PIN_NUMBER 50

#define MODE_OUTPUT 0
#define MODE_INPUT 1

#define VALUE_LOW 0
#define VALUE_HIGH 1

#define SUCCESS 1
#define PIN_NOT_DEFINED_ERROR 2
#define WRONG_MODE_ERROR 3


typedef struct {
    bool defined;
    int mode;
    int value;
} PinState;

int reg_get_pin_mode(int pin_number);
void reg_set_pin_mode(int pin_number, int mode);

int reg_get_pin_value(int pin_number);
int reg_set_pin_value(int pin_number, int value);

PinState* reg_dump_pin_data();

#endif
