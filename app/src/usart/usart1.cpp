//
// USARTインタフェース #1 (I/Fレジスタ設定)
//
#include <avr/io.h>

#include "usart.hpp"

#ifdef MCU_HAS_USART1

#ifndef bit_set
#define bit_set(v, n) v |= _BV(n)
#endif
#ifndef bit_reset
#define bit_reset(v, n) v &= ~_BV(n)
#endif
#ifndef bit_get
#define bit_get(v, n) (v & _BV(n)) >> n
#endif

namespace usart {

USART1::USART1() : BaseUSART(&UDR1) {}

void USART1::setBaudRate(const uint64_t& baudrate) const {
    // `UBRRn`(ボーレートレジスタ)に設定する値の計算
    // (ボーレートを2で割っているのは倍速設定上の都合. 最後に0.5を加算しているのは誤差修正のため.)
    const double ubrr_value = (static_cast<uint64_t>(F_CPU) / (baudrate / 2) / 16.0) - 1.0 + 0.5;

    // レジスタに設定
    UBRR1H = (uint8_t)(static_cast<uint16_t>(ubrr_value) >> 8);
    UBRR1L = (uint8_t)(static_cast<uint16_t>(ubrr_value) & 0xFF);

    // 倍速許可
    UCSR1A |= _BV(U2X1);
}

void USART1::setSendability(bool isEnable) const {
    isEnable ? bit_set(UCSR1B, TXEN1) : bit_reset(UCSR1B, TXEN1);
}

bool USART1::getSendability() const {
    return bit_get(UCSR1B, TXEN1);
}

void USART1::setReceivability(bool isEnable) const {
    isEnable ? bit_set(UCSR1B, RXEN1) : bit_reset(UCSR1B, RXEN1);
}

bool USART1::getReceivability() const {
    return bit_get(UCSR1B, RXEN1);
}

void USART1::setSendBufferInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR1B, UDRIE1);
    } else {
        bit_reset(UCSR1B, UDRIE1);
    }
}

void USART1::setReceiveInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR1B, RXCIE1);
    } else {
        bit_reset(UCSR1B, RXCIE1);
    }
}

}  // namespace usart

#endif
