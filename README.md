# avr-serial

## Overview

Generic UART interface library for AVR microcontroller

## Installation

This repository depends on [cmake-avr](https://github.com/Enchan1207/cmake-avr) and [arduino-cli](https://github.com/arduino/arduino-cli).
Before use this library, please install AVR core of arduino-cli:

```
arduino-cli core install arduino:avr
```

This project compiles for the MCU specified at build time and generates library `libuart.a`. Therefore, libraries should be built for each project.
Recommended way is using FetchContent to add this library as dependency.

Add the following to CMakeLists.txt:

```cmake
include(FetchContent)
FetchContent_Declare(
    avr-serial
    GIT_REPOSITORY https://github.com/Enchan1207/avr-serial
    GIT_TAG v0.2.0
)
FetchContent_MakeAvailable(avr-serial)
```

### Usage

This library provides class `Serial` similar to Arduinos.
If MCU has multiple UART interfaces, `Serial1` , `Serial2`, ... is also defined (Actually, `Serial` is macro of `Serial0`).

For example:

```c++: main.cpp
// file: main.cpp
//
// Simple transmit loop
//
#include <avr/interrupt.h>

#include "uart/uart.hpp"

using namespace uart;

int main() {
    sei();
    Serial.begin(115200);

    while(true){
        Serial.println("Hello, World!");
        _delay_ms(1000);
    }
}

// USART, Data Register Empty
ISR(USART_UDRE_vect) {
    Serial0.onSendBufferEmpty();
}

// USART Rx Complete
ISR(USART_RX_vect) {
    Serial0.onReceive();
}
```

**NOTE**: avr-serial internally controls communication using interrupts, but only provides functions that should be executed within the ISR, and does not provide an ISR implementation. Therefore, you must define ISRs for `UDRE_vect` and `RX_vect` in your application code.


## License

This repository is published under [MIT License](LICENSE).
