//
// UARTインタフェース (イベントハンドリング)
//
#include "uart/interface/base.hpp"

namespace uart {

void UART::onSendBufferEmpty() {
    // 送信バッファが空なら、割り込みを無効化して戻る
    if (internalSendBuffer.isEmpty()) {
        setSendBufferInterruption(false);
        return;
    }

    // 該当する位置のデータを読み出しUDR0へ書き込み
    uint8_t data = 0;
    if (internalSendBuffer.pop(&data) != BufferResult::Success) {
        return;
    }
    *(registerMap.data) = data;
}

void UART::onReceive() {
    // UDRから読み出す
    const uint8_t data = *(registerMap.data);

    // 受信バッファに書き込み
    internalRecvBuffer.append(data);
}

}  // namespace uart
