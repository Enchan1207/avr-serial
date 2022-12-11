//
// USARTインタフェース
//
#include "usart.h"

#include <avr/io.h>

#ifndef bit_set
#define bit_set(v, n) v |= _BV(n)
#endif
#ifndef bit_reset
#define bit_reset(v, n) v &= ~_BV(n)
#endif

void USART::begin(const uint64_t& baudrate) const {
    // ボーレート設定
    const uint64_t ubrr_value = (uint64_t)F_CPU / 16 / (baudrate - 1);
    UBRR0 = (uint16_t)ubrr_value;

    // 送受信有効化
    UCSR0B |= _BV(TXEN0) | _BV(RXEN0);
}

bool USART::_write(const uint8_t data) {
    // バッファがいっぱい(tailの次がhead)なら、戻る
    const buffer_size_t head = internalSendBuffer.head;
    const buffer_size_t tail = internalSendBuffer.tail;
    const buffer_size_t nextTail = (tail + 1) % internalUSARTBufferSize;
    if (nextTail == head) {
        return false;
    }

    // tailの位置にdataを書き込み
    internalSendBuffer.rawData[tail] = data;

    // tailを進める
    internalSendBuffer.tail = nextTail;

    return true;
}

size_t USART::_print(const char* const str) {
    // バッファが詰まるまで流し込む
    size_t sentBytesCount = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (!_write(str[i])) {
            break;
        }
        sentBytesCount++;
    }
    return sentBytesCount;
}

size_t USART::print(const char* const str) {
    // 書き込み
    size_t sentBytesCount = _print(str);

    // UDRE割り込みを有効化して戻る
    bit_set(UCSR0B, UDRIE0);
    return sentBytesCount;
}

size_t USART::println(const char* const str) {
    // 書き込み
    size_t sentBytesCount = _print(str);

    // 改行
    bool result = _write('\n');
    if (result) {
        sentBytesCount++;
    }

    // UDRE割り込みを有効化して戻る
    bit_set(UCSR0B, UDRIE0);
    return sentBytesCount;
}

bool USART::write(const uint8_t data) {
    // 1byte分送信バッファに追加
    bool result = _write(data);

    // UDRE割り込みを有効化して戻る
    bit_set(UCSR0B, UDRIE0);
    return result;
}

void USART::onUDREmpty() {
    // 送信バッファが空(head = tail) なら、割り込みを無効化して戻る
    if (internalSendBuffer.head == internalSendBuffer.tail) {
        bit_reset(UCSR0B, UDRIE0);
        return;
    }

    // 該当する位置のデータをUDR0へ書き込み
    const buffer_size_t head = internalSendBuffer.head;
    UDR0 = internalSendBuffer.rawData[head];

    // headを進める
    internalSendBuffer.head = (head + 1) % internalUSARTBufferSize;
}
