//
// エコーバック
//
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdlib.h>

#include "uart/uart.hpp"

using namespace uart;

int main() {
    sei();
    Serial.begin(115200);

    while (true) {
        uint8_t data = '\0';
        while (!Serial.read(&data)) {
            // データが来るまで待つ
        }
        Serial.write(data);
    }
}
