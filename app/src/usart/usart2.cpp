//
// USARTインタフェース #2 (I/Fレジスタ設定)
//
#include <avr/io.h>

#include "usart.hpp"

#ifdef MCU_HAS_USART2

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

USART2::USART2() : BaseUSART(&UDR2) {}

void USART2::setBaudRate(const uint64_t& baudrate) const {
    // `UBRRn`(ボーレートレジスタ)に設定する値の計算
    // (ボーレートを2で割っているのは倍速設定上の都合. 最後に0.5を加算しているのは誤差修正のため.)
    const double ubrr_value = (static_cast<uint64_t>(F_CPU) / (baudrate / 2) / 16.0) - 1.0 + 0.5;

    // レジスタに設定
    UBRR2H = (uint8_t)(static_cast<uint16_t>(ubrr_value) >> 8);
    UBRR2L = (uint8_t)(static_cast<uint16_t>(ubrr_value) & 0xFF);

    // 倍速許可
    UCSR2A |= _BV(U2X2);
}

void USART2::setSendability(bool isEnable) const {
    isEnable ? bit_set(UCSR2B, TXEN2) : bit_reset(UCSR2B, TXEN2);
}

bool USART2::getSendability() const {
    return bit_get(UCSR2B, TXEN2);
}

void USART2::setReceivability(bool isEnable) const {
    isEnable ? bit_set(UCSR2B, RXEN2) : bit_reset(UCSR2B, RXEN2);
}

bool USART2::getReceivability() const {
    return bit_get(UCSR2B, RXEN2);
}

void USART2::setSendBufferInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR2B, UDRIE2);
    } else {
        bit_reset(UCSR2B, UDRIE2);
    }
}

void USART2::setReceiveInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR2B, RXCIE2);
    } else {
        bit_reset(UCSR2B, RXCIE2);
    }
}

}  // namespace usart

#endif
