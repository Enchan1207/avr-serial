//
// USARTインタフェース (イベントハンドリング)
//
#include <avr/io.h>

#include "usart.h"

void USART::onSendBufferEmpty() {
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

void USART::onReceive() {
    // UDRから読み出す
    const uint8_t data = UDR0;

    // バッファがいっぱい(tailの次がhead)なら、読み捨てる
    const buffer_size_t head = internalRecvBuffer.head;
    const buffer_size_t tail = internalRecvBuffer.tail;
    const buffer_size_t nextTail = (tail + 1) % internalUSARTBufferSize;
    if (nextTail == head) {
        return;
    }

    // 受信バッファに書き込み
    internalRecvBuffer.rawData[tail] = data;

    // tailを進める
    internalRecvBuffer.tail = nextTail;
}
