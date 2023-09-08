//
// UARTインタフェース (基本的な送受信)
//
#include <string.h>

#include "uart/interface/base.hpp"

namespace uart {

size_t UART::write(const uint8_t data) {
    waitForSendBufferAvailable();
    internalSendBuffer.append(data);
    setSendBufferInterruption(true);
    return 1;
}

size_t UART::write(const char* const data) {
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

bool UART::read(uint8_t* const data) {
    const BufferResult result = internalRecvBuffer.pop(data);
    return result == BufferResult::Success;
}

}  // namespace uart
