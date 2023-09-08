//
// 単純な文字の表示
//
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "uart/uart.hpp"

using namespace uart;

int main() {
    sei();
    Serial.begin(115200);

    // バッファに収まる範囲の文字列

    // オンメモリ
    char const* shortMessageOnMemory = "message stored in SRAM";
    Serial.println(shortMessageOnMemory);

    // Flash
    auto shortMessageOnFlash = PSTR("message stored in Flash");
    Serial.println_P(shortMessageOnFlash);

    // バッファ長を上回る文字列

    // オンメモリ
    char const* longMessageOnMemory = "A long message stored in SRAM was sent via UART.";
    Serial.println(longMessageOnMemory);

    // Flash
    auto longMessageOnFlash = PSTR("A long message stored in Flash was sent via UART.");
    Serial.println_P(longMessageOnFlash);

    abort();
}
