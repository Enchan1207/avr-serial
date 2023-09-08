//
// UARTインタフェース 基底クラス
//

#include "uart/interface/base.hpp"

#ifndef bit_set
#define bit_set(v, n) v |= _BV(n)
#endif
#ifndef bit_reset
#define bit_reset(v, n) v &= ~_BV(n)
#endif
#ifndef bit_get
#define bit_get(v, n) (v & _BV(n)) >> n
#endif
#ifndef bit_setval
#define bit_setval(state, v, n) state ? bit_set(v, n) : bit_reset(v, n)
#endif

namespace uart {

void UART::waitForSendBufferAvailable() const {
    // 送信バッファ割り込みを有効化 (無限ループ防止)
    setSendBufferInterruption(true);

    // 待機
    volatile bool isFull = internalSendBuffer.isFull();
    while (isFull) {
        isFull = internalSendBuffer.isFull();
    }
}

void UART::setBaudRate(const uint64_t& baudrate) const {
    // `UBRRn`(ボーレートレジスタ)に設定する値の計算
    // (ボーレートを2で割っているのは倍速設定上の都合. 最後に0.5を加算しているのは誤差修正のため.)
    const double ubrr_value = (static_cast<uint64_t>(F_CPU) / (baudrate / 2) / 16.0) - 1.0 + 0.5;

    // レジスタに設定
    *(registerMap.baudrateHigh) = (uint8_t)(static_cast<uint16_t>(ubrr_value) >> 8);
    *(registerMap.baudrateLow) = (uint8_t)(static_cast<uint16_t>(ubrr_value) & 0xFF);

    // 倍速許可
    *(registerMap.stateAndControlA) |= _BV(registerMap.doubleSpeedEnableBitPos);
}

void UART::setSendability(bool isEnable) const {
    bit_setval(isEnable, *(registerMap.stateAndControlB), registerMap.txEnableBitPos);
}

bool UART::getSendability() const {
    return bit_get(*(registerMap.stateAndControlB), registerMap.txEnableBitPos);
}

void UART::setReceivability(bool isEnable) const {
    bit_setval(isEnable, *(registerMap.stateAndControlB), registerMap.rxEnableBitPos);
}

bool UART::getReceivability() const {
    return bit_get(*(registerMap.stateAndControlB), registerMap.rxEnableBitPos);
}

void UART::setSendBufferInterruption(bool isEnable) const {
    bit_setval(isEnable, *(registerMap.stateAndControlB), registerMap.txInterruptEnableBitPos);
}

void UART::setReceiveInterruption(bool isEnable) const {
    bit_setval(isEnable, *(registerMap.stateAndControlB), registerMap.rxInterruptEnableBitPos);
}

}  // namespace uart
