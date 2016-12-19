void setup()
{
    pinMode(0, OUTPUT);
    test(0);
}

void loop()
{

}

// Test function prototypes.
void test(int pin)
{
    digitalWrite(pin, HIGH);
}
