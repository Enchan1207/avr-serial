//
// SerialComm
//
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "usart.h"

#define bit_set(v, n) v |= _BV(n)
#define bit_reset(v, n) v &= ~_BV(n)

USART usart;

constexpr uint8_t builtInLEDOffset = 5;  // Dev board has Built-in LED @ PORTB:5

int main() {
    // initialize GPIO
    bit_set(DDRB, builtInLEDOffset);
    bit_reset(PORTB, builtInLEDOffset);

    // enable interrupt
    sei();

    // Initialize UART
    usart.begin(115200);

    _delay_ms(1000);

    while (true) {
        usart.println("Hello, World!");

        // indicate
        bit_set(PORTB, builtInLEDOffset);
        _delay_ms(500);
        bit_reset(PORTB, builtInLEDOffset);
        _delay_ms(500);
    }
}
