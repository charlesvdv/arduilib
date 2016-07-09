#ifndef _REG_PIN_H
#define _REG_PIN_H

#define PIN_NUMBER 50

typedef enum {
    MODE_INPUT = 1,
    MODE_OUTPUT = 0
} Mode;

typedef enum {
    VALUE_LOW = 0,
    VALUE_HIGH = 1
} Value;

typedef struct {
    bool defined;
    Mode mode;
    Value value;
} PinState;

Mode reg_get_pin_mode(int pin_number);
void reg_set_pin_mode(int pin_number, Mode mode); 

Value reg_get_pin_value(int pin_number);
void reg_set_pin_value(int pin_number, Value value);

#endif
