# Arduinint
[![Build Status](https://travis-ci.org/charlesvdv/arduinint.svg?branch=master)](https://travis-ci.org/charlesvdv/arduinint)

Arduinint is an ARDUINo INTerpreter build to compile and test arduino
code on your computer.

## How is it working ?

Arduino code is just a C program with a great library on top of it.
Arduinint is trying to recreate this library but instead of
seeing the effect of your code on the Arduino board,
we are using a JSON dump to show the pins' state

This JSON dump could be used to analyse the result for students exercices
or to show the result in a GUI.

## How to use it ?

For the moment, you just have to modify the arduino code in *arduino.c* and
run `make all && ./arduino` to test your code.

### Dependencies

- [jansson](https://github.com/akheron/jansson)
- [cmocka](https://cmocka.org/) for testing only.

## Supported Arduino functions

- [x] digitalRead, digitalWrite and pinMode
- [x] millis, micros
- [x] delai, delaiMicroseconds
- [ ] attachInterrupt, detachInterrupt
- [ ] analogRead, analogWrite
- [ ] Serial.read, Serial.write
