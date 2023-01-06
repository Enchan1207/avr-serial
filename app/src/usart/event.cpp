//
// USARTインタフェース (イベントハンドリング)
//
#include <avr/io.h>

#include "usart.h"

void USART::onSendBufferEmpty() {
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
    UDR0 = data;
}

void USART::onReceive() {
    // UDRから読み出す
    const uint8_t data = UDR0;

    // 受信バッファに書き込み
    internalRecvBuffer.append(data);
}
