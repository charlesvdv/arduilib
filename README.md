# Arduinint
[![Build Status](https://travis-ci.org/charlesvdv/arduinint.svg?branch=master)](https://travis-ci.org/charlesvdv/arduinint)

Interpret your arduino code into JSON. **arduinint** stands for ARDUIno INTerpreter.

## Usage

Interpret code with **arduinint** is very straightforward. Firstly, you will need to write a
configuration for the interpreter. See this [part of the wiki](https://github.com/charlesvdv/arduinint/wiki/Configuration).
The simplest configuration is just giving the board like this:
```json
{
    "board": "uno"
}
```

We can now interpret the code. Let's take an example for the *tests* folder. We will take the
[input read test](https://github.com/charlesvdv/arduinint/tree/master/tests/test_input_read). We
launch the interpret by typing in the terminal:
```bash
./arduinint interpret --config tests/test_input_read/config.json tests/test_input_read/test.ino
```

**arduinint** returns, if no errors are found, a JSON with all the IO informations. The JSON looks
like this:
```json
{
  "io": [
    {
      "time": 0,
      "value": [
        {
          "pin": 0,
          "mode": 1,
          "value": 0,
          "forced": false
        },
        {
          "pin": 1,
          "mode": 0,
          "value": 0,
          "forced": false
        }
      ]
    },
    {
      "time": 5,
      "value": [
        {
          "pin": 0,
          "mode": 1,
          "value": 1,
          "forced": false
        },
        {
          "pin": 1,
          "mode": 0,
          "value": 1,
          "forced": false
        }
      ]
    }
  ]
}
```
We can see that at time 0, the pins 0 and 1 was in a LOW state. At the time 5, both pins are passed
at the state HIGH.

## Arduino support
The board and arduino library is currently being worked. Here is what is currently supported and
what is expected to come.

### Board

- [UNO](https://www.arduino.cc/en/Main/ArduinoBoardUno)

### Functions

- [x] digitalRead, digitalWrite and pinMode
- [x] millis, micros
- [x] delai, delaiMicroseconds
- [ ] attachInterrupt, detachInterrupt
- [ ] analogRead, analogWrite
- [ ] Serial functions
- [ ] Math functions
- [ ] Random numbers functions
- [ ] Char functions

## How is it working ?

As you may already know, *arduino* is a suite of tooling (function prototype generator, ...) and a
library implementing low level micro-controller functions. The language itself is just C/C++.

**arduinint** is just a redefinition of this library and a naïve implementation of a
micro-controller functions (see [microclib](https://github.com/charlesvdv/arduinint/tree/master/microclib)).
When the *arduino* code is running, **arduinint** will save data on IO states to image the pins state
over time. Currently, the program is outputting a JSON showing the IO states history and possible
errors due to faulty configuration.

The board input are configured before running the interpreter. See
[the wiki](https://github.com/charlesvdv/arduinint/wiki/Configuration#io-events-configuration) for
more informations.

## Dependencies

- [jansson](https://github.com/akheron/jansson)
- [meson](https://github.com/mesonbuild/meson) and [ninja](https://github.com/ninja-build/ninja) for the build system.
- [cmocka](https://cmocka.org/) for testing only.
