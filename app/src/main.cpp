//
// SerialComm
//
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define BAUDRATE 115200

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

int main() {
    // Initialize UART
    initSerial(BAUDRATE);

    // message to send
    const char message[] = "Hello, World! now I can set baudrate from function (not hard-coded)!\n";
    uint8_t currentIndex = 0;

    // loop
    while (true) {
        // 送信できるようになるまで待つ
        loop_until_bit_is_set(UCSR0A, UDRE0);

        // データレジスタに送信
        const char next = message[currentIndex];
        UDR0 = next;

        // 改行を送ったら休む
        if (next == '\n') {
            _delay_ms(1000);
        }

        // インデックスを進める
        currentIndex = (currentIndex + 1) % sizeof(message);
    }
}
