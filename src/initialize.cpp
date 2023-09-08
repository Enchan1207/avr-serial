//
// UARTインタフェース (初期化)
//

#include "uart/interface/base.hpp"

namespace uart {

void UART::begin(const uint64_t& baudrate) const {
    // ボーレート設定
    setBaudRate(baudrate);

    // 送受信有効化
    setReceivability(true);
    setSendability(true);

    // 割り込み有効化
    setSendBufferInterruption(true);
    setReceiveInterruption(true);
}

}  // namespace uart
