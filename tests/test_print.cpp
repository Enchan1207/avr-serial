//
// 単純な文字の表示
//
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "uart/uart.hpp"

#ifndef MESSAGE
#define MESSAGE "Hello,World"
#endif

using namespace uart;

int main() {
    sei();
    Serial.begin(115200);

#ifdef READ_FROM_FLASH
    auto message = PSTR(MESSAGE);
    Serial.print_P(message);
#else
    char const* message = MESSAGE;
    Serial.print(message);
#endif

    abort();
}
