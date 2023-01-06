//
// USARTインタフェース(送受信)
//
#include <avr/io.h>

#include "usart.h"

size_t USART::write(const uint8_t data) {
    waitForSendBufferAvailable();
    internalSendBuffer.append(data);
    setSendBufferInterruption(true);
    return 1;
}

size_t USART::write(const char* const data) {
    if (data == nullptr) {
        return 0;
    }

    size_t dataLength = strlen(data);
    for (size_t i = 0; i < dataLength; i++) {
        waitForSendBufferAvailable();
        internalSendBuffer.append(*(data + i));
        setSendBufferInterruption(true);
    }

    return dataLength;
}

size_t USART::print(const char* const str) {
    // 実質writeですが、フォーマット変換とかその辺を考える場合のために残しています
    return write(str);
}

size_t USART::println(const char* const str) {
    return write(str) + write("\r\n");
}

bool USART::read(uint8_t* const data) {
    const BufferResult result = internalRecvBuffer.pop(data);
    return result == BufferResult::Success;
}
