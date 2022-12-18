//
// USARTインタフェース (I/Fレジスタ設定)
//
#include <avr/io.h>

#include "usart.h"

#ifndef bit_set
#define bit_set(v, n) v |= _BV(n)
#endif
#ifndef bit_reset
#define bit_reset(v, n) v &= ~_BV(n)
#endif

void USART::setBaudRate(const uint64_t& baudrate) const {
    // `UBRRn`(ボーレートレジスタ)に設定する値の計算
    // (ボーレートを2で割っているのは倍速設定上の都合. 最後に0.5を加算しているのは誤差修正のため.)
    const double ubrr_value = ((uint64_t)F_CPU / (baudrate / 2) / 16.0) - 1.0 + 0.5;

    // 倍速許可
    UCSR0A |= _BV(U2X0);

    // レジスタに設定
    UBRR0 = (uint16_t)ubrr_value;
}

void USART::setComuunicatability(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR0B, TXEN0);
        bit_set(UCSR0B, RXEN0);
    } else {
        bit_reset(UCSR0B, TXEN0);
        bit_reset(UCSR0B, RXEN0);
    }
}

void USART::setSendBufferInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR0B, UDRIE0);
    } else {
        bit_reset(UCSR0B, UDRIE0);
    }
}

void USART::setReceiveInterruption(bool isEnable) const {
    if (isEnable) {
        bit_set(UCSR0B, RXCIE0);
    } else {
        bit_reset(UCSR0B, RXCIE0);
    }
}
