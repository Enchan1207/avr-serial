//
// SerialComm
//
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define BAUDRATE 115200
#define LED_BUILTIN 5  // Dev board has Built-in LED @ PORTB:5
#define bit_set(v, n) v |= _BV(n)
#define bit_reset(v, n) v &= ~_BV(n)

// 最後に受信した値
int16_t* LastChar;

/**
 * @brief initialize Serial communication interface (UART).
 *
 * @param baudrate
 */
void initSerial(const uint64_t& baudrate) {
    // baudrate
    const uint64_t ubrr_value = (uint64_t)F_CPU / 16 / (baudrate - 1);
    UBRR0 = (uint16_t)ubrr_value;

    // enable interrupt
    UCSR0B |= _BV(TXCIE0) | _BV(RXCIE0) | _BV(UDRIE0);

    // allow to send/recv
    UCSR0B |= _BV(TXEN0) | _BV(RXEN0);
}

/**
 * 送信バッファ空き
 */
ISR(USART_UDRE_vect) {
    // 送信するべきデータがなければ戻る
    if (*LastChar == -1) {
        return;
    }

    // データバッファに書き出す
    UDR0 = (char)*LastChar;
    *LastChar = -1;

    bit_reset(PORTB, LED_BUILTIN);
}

/**
 * 受信完了
 */
ISR(USART_RX_vect) {
    bit_set(PORTB, LED_BUILTIN);

    // データバッファに取り込む
    *LastChar = UDR0;
}

int main() {
    // initialize GPIO
    bit_set(DDRB, LED_BUILTIN);
    bit_reset(PORTB, LED_BUILTIN);

    // initialize USART buffer
    int16_t lastChar = -1;
    LastChar = &lastChar;

    // enable interrupt
    sei();

    // Initialize UART
    initSerial(BAUDRATE);

    while (true) {
        /* do nothing in loop */
    }
}
