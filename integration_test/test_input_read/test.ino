void setup() {
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
}

void loop() {
    if (digitalRead(0) == HIGH) {
        digitalWrite(1, HIGH);
    }
}
