void setup() {
    // Setup pins for the loop test.
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
}

int value = 0;
void loop() {
    if (value != micros()) {
        digitalWrite(0, HIGH);
    }
    if (micros() == 10) {
        digitalWrite(1, HIGH);
    }
    // Check if the interpret don't go too far in time.
    if (micros() > 10) {
        digitalWrite(2, HIGH);
    }
    value++;
}
