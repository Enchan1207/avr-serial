//
// USARTインタフェース (初期化)
//
#include <avr/io.h>

#include "usart.h"

void USART::begin(const uint64_t& baudrate) const {
    // ボーレート設定
    const uint64_t ubrr_value = (uint64_t)F_CPU / 16 / (baudrate - 1);
    UBRR0 = (uint16_t)ubrr_value;

    // 送受信有効化
    setComuunicatability(true);
}
