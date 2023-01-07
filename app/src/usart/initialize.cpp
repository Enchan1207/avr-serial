//
// USARTインタフェース (初期化)
//

#include "usart.h"

void USART::begin(const uint64_t& baudrate) const {
    // ボーレート設定
    setBaudRate(baudrate);

    // 送受信有効化
    setComuunicatability(true);

    // 割り込み有効化
    setSendBufferInterruption(true);
    setReceiveInterruption(true);
}
