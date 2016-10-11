#ifndef ARDNO_INTERRUPT_H
#define ARDNO_INTERRUPT_H

void attachInterrupt(int interrupt, void (*ISR)(void), int mode);

void detachInterrupt(int interrupt);

void interrupts();

void noInterrupts();

#endif
