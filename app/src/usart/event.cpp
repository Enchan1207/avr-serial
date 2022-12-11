//
// USARTインタフェース (イベントハンドリング)
//
#include <avr/io.h>

#include "usart.h"

void USART::onUDREmpty() {
    // 送信バッファが空(head = tail) なら、割り込みを無効化して戻る
    if (internalSendBuffer.head == internalSendBuffer.tail) {
        setSendBufferInterruption(false);
        return;
    }

    // 該当する位置のデータをUDR0へ書き込み
    const buffer_size_t head = internalSendBuffer.head;
    UDR0 = internalSendBuffer.rawData[head];

    // headを進める
    internalSendBuffer.head = (head + 1) % internalUSARTBufferSize;
}
