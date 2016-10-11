# Arduinint
[![Build Status](https://travis-ci.org/charlesvdv/arduinint.svg?branch=master)](https://travis-ci.org/charlesvdv/arduinint)

**Arduinint** is an implementation of the arduino library build to understand the arduino code
on your computer. **Arduinint** stand for ARDUIno INTerpreter.

## How to use it ?

Interpret code with **arduinint** is very straightforward. First, you will need to create a JSON
file that will configure the interpreter. Here is the most simple config that you can create:

```json
{
    "board": "uno"
}
```

That's it (for more settings, see the [wiki](https://github.com/charlesvdv/arduinint/wiki)).
The next thing to do is running:

```
./arduinint interpret --config path/to/config.json path/to/arduino-code.ino
```

**Arduinint** returns, if no errors are found, a JSON with all the IO informations.

## How is it working ?

As you may already know, *arduino* is a suite of tooling (function prototype generator, ...) and a
library implementing low level micro-controller functions. The language itself is just C/C++.

**Arduinint** is just a redefinition of this library and a simple implementation of a micro-controller
functions (see microclib). When the *arduino* code is running, **arduinint** will save data on IO states
to image afterward the result of the *arduino* code. Currently, the program is outputting a JSON
showing the IO states history and possible errors due to faulty configuration.

## Dependencies

- [jansson](https://github.com/akheron/jansson)
- [meson](https://github.com/mesonbuild/meson) for the build system.
- [cmocka](https://cmocka.org/) for testing only.

## Arduino support
### Board

- uno

### Functions

- [x] digitalRead, digitalWrite and pinMode
- [x] millis, micros
- [x] delai, delaiMicroseconds
- [ ] attachInterrupt, detachInterrupt
- [ ] analogRead, analogWrite
- [ ] Serial functions
- [ ] **easy** Math functions
- [ ] **easy** Random numbers functions
- [ ] **easy** Char functions

Functions tagged **easy** are functions easy to implement for someone looking to begin contributing
in the project.
