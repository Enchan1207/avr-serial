//
// USARTインタフェース (初期化)
//
#include <avr/io.h>

#include "usart.h"

void USART::begin(const uint64_t& baudrate) const {
    // ボーレート設定
    const double ubrr_value = ((uint64_t)F_CPU / baudrate / 16.0) - 1.0 + 0.5;
    UBRR0 = (uint16_t)ubrr_value;

    // 送受信有効化
    setComuunicatability(true);

    // 割り込み有効化
    setSendBufferInterruption(true);
    setReceiveInterruption(true);
}
