// in here you will copy paste the arduino code that you want to
// test
#include <stdio.h>

#include "arduilib/arduilib_io.h"
#include "arduilib/arduilib_time.h"

void setup() {
    pinMode(12, OUTPUT);
}

void loop() {
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
    delay(1000);
}
