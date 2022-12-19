//
// USARTインタフェース(送受信)
//
#include <avr/io.h>

#include "usart.h"

bool USART::_write(const uint8_t data) {
    const BufferResult result = internalSendBuffer.append(data);
    return result == BufferResult::Success;
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
    setSendBufferInterruption(true);
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
    setSendBufferInterruption(true);
    return sentBytesCount;
}

bool USART::write(const uint8_t data) {
    // 1byte分送信バッファに追加
    bool result = _write(data);

    // UDRE割り込みを有効化して戻る
    setSendBufferInterruption(true);
    return result;
}

bool USART::read(uint8_t* const data) {
    const BufferResult result = internalRecvBuffer.pop(data);
    return result == BufferResult::Success;
}
