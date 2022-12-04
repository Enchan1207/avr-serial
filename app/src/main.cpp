//
// SerialComm
//
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define BAUDRATE 115200
#define LED_BUILTIN 5  // Dev board has Built-in LED @ PORTB:5

/**
 * @brief initialize Serial communication interface (UART).
 *
 * @param baudrate
 */
void initSerial(const uint64_t& baudrate) {
    // baudrate
    const uint64_t ubrr_value = (uint64_t)F_CPU / 16 / (baudrate - 1);
    UBRR0 = (uint16_t)ubrr_value;

    // allow to send
    UCSR0B = _BV(TXEN0);
}

/**
 * 送信バッファ空き
 */
ISR(USART_UDRE_vect) {
    // latch built-in led
    PORTB &= ~_BV(LED_BUILTIN);
}

void main() {
    // Initialize GPIO
    DDRB |= _BV(LED_BUILTIN);
    PORTB |= _BV(LED_BUILTIN);

    // enable interrupt
    sei();

    // Initialize UART
    initSerial(BAUDRATE);

    while (true) {
        /* do nothing in loop */
    }
}
