//
// USARTインタフェース #3 (I/Fレジスタ設定)
//
#include <avr/io.h>

#include "usart.hpp"

#ifdef MCU_HAS_USART3

#ifndef bit_set
#define bit_set(v, n) v |= _BV(n)
#endif
#ifndef bit_reset
#define bit_reset(v, n) v &= ~_BV(n)
#endif

namespace usart {

USART3::USART3() : BaseUSART(&UDR3) {}

void USART3::setBaudRate(const uint64_t& baudrate) const {
    // `UBRRn`(ボーレートレジスタ)に設定する値の計算
    // (ボーレートを2で割っているのは倍速設定上の都合. 最後に0.5を加算しているのは誤差修正のため.)
    const double ubrr_value = (static_cast<uint64_t>(F_CPU) / (baudrate / 2) / 16.0) - 1.0 + 0.5;

    // レジスタに設定
    UBRR3H = (uint8_t)(static_cast<uint16_t>(ubrr_value) >> 8);
    UBRR3L = (uint8_t)(static_cast<uint16_t>(ubrr_value) & 0xFF);

    // 倍速許可
    UCSR3A |= _BV(U2X3);
}

void USART3::setComuunicatability(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR3B, TXEN2);
        bit_set(UCSR3B, RXEN2);
    } else {
        bit_reset(UCSR3B, TXEN2);
        bit_reset(UCSR3B, RXEN2);
    }
}

void USART3::setSendBufferInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR3B, UDRIE3);
    } else {
        bit_reset(UCSR3B, UDRIE3);
    }
}

void USART3::setReceiveInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR3B, RXCIE2);
    } else {
        bit_reset(UCSR3B, RXCIE2);
    }
}

}  // namespace usart

#endif
