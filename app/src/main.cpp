//
// SerialComm
//
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <util/delay.h>

#include "usart.hpp"

#define bit_set(v, n) v |= _BV(n)
#define bit_reset(v, n) v &= ~_BV(n)

constexpr uint8_t builtInLEDOffset = 5;  // Dev board has Built-in LED @ PORTB:5

int main() {
    // initialize GPIO
    bit_set(DDRB, 2);
    bit_reset(PORTB, 2);

    // enable interrupt
    sei();

    // Initialize USART
    Serial.begin(115200);

    Serial.println((unsigned char)22);
    Serial.println(123);
    Serial.println((unsigned int)456);
    Serial.println(3.14);
    Serial.println(123456L);
    Serial.println(1234567890UL);

    while (true) {
        // 64文字
        Serial.println_P(PSTR("leYD5Uel8bVJvWSbNt9psWWqFveCMyj1MXmUhx41tBZAEz9uErnMxTkFP7T1sw"));

        // 65文字
        // Serial.println("leYD5Uel8bVJvbNt9psWWqFveCMyj1MXmUhx41tBZAEz9uErnMxTkFP7T1sABCc");

        // 70文字
        // Serial.println("leYD5Uel8bVJvWSbNt9psWWqFveCMyj1MXhx41tBZAEz9uErnMxTkFP7T1sAABCDEaed");

        // 128文字
        // Serial.println("DPCBFAbczcGMOFRPGFPMWqbsAJME6C4yCAjXSOr3whWUm1Rls2zNuxPDpO7a7xxJMSwSmOI9oE0nmBDCMyoOwybFbZqMG7sfj1ZnCBFToxOU04NzUr3XHXQcVUakfy");

        // 256文字
        // Serial.println("eIiBORa4NVGK3AtVPUwLBIYr7gOXMwmrooehUXfnHr6ZbAaHa2dOqF32RIgCYk71xHoTmxmxBhAa2U3QEsxe3M2hVJ8qTsIDS2Kt1xcFCAC96TxH8Qu1pjpSGYfV6BmoFJ85qHvWlzOoHWHp5HExT6e3d9G8f4YnbubBnqTo6hW9q3Y6aupIrR9jcG2dPXTcfwr9LVsj0aN755pUvURxMGsQ6yUTFAuPJYhqz97cJp9mPWnSpy6V2MWPgOAFmz");

        // 送信完了のインジケータ
        bit_set(PORTB, 2);
        _delay_ms(500);
        bit_reset(PORTB, 2);
        _delay_ms(500);
    }
}
