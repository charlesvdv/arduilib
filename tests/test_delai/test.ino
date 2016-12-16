void setup() {
    pinMode(0, OUTPUT);
}

void loop() {
    digitalWrite(0, HIGH);
    delayMicroseconds(1);
    digitalWrite(0, LOW);
    delayMicroseconds(1);
}
