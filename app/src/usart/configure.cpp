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
