//
// USARTインタフェース #0 (I/Fレジスタ設定)
//
#include <avr/io.h>

#include "usart/impl.hpp"

#ifdef MCU_HAS_USART0

#ifndef bit_set
#define bit_set(v, n) v |= _BV(n)
#endif
#ifndef bit_reset
#define bit_reset(v, n) v &= ~_BV(n)
#endif
#ifndef bit_get
#define bit_get(v, n) (v & _BV(n)) >> n
#endif

// レジスタ名ほかの表記揺れを吸収
#if defined(UDR) && !defined(UDR0)

// レジスタ名
#define UDR0 UDR
#define UBRR0H UBRRH
#define UBRR0L UBRRL
#define UCSR0A UCSRA
#define UCSR0B UCSRB

// フラグのビット位置
#define TXEN0 TXEN
#define RXEN0 RXEN
#define U2X0 U2X
#define UDRIE0 UDRIE
#define RXCIE0 RXCIE

#endif

namespace usart {

USART0::USART0() : BaseUSART(&UDR0) {}

void USART0::setBaudRate(const uint64_t& baudrate) const {
    // `UBRRn`(ボーレートレジスタ)に設定する値の計算
    // (ボーレートを2で割っているのは倍速設定上の都合. 最後に0.5を加算しているのは誤差修正のため.)
    const double ubrr_value = (static_cast<uint64_t>(F_CPU) / (baudrate / 2) / 16.0) - 1.0 + 0.5;

    // レジスタに設定
    UBRR0H = (uint8_t)(static_cast<uint16_t>(ubrr_value) >> 8);
    UBRR0L = (uint8_t)(static_cast<uint16_t>(ubrr_value) & 0xFF);

    // 倍速許可
    UCSR0A |= _BV(U2X0);
}

void USART0::setSendability(bool isEnable) const {
    isEnable ? bit_set(UCSR0B, TXEN0) : bit_reset(UCSR0B, TXEN0);
}

bool USART0::getSendability() const {
    return bit_get(UCSR0B, TXEN0);
}

void USART0::setReceivability(bool isEnable) const {
    isEnable ? bit_set(UCSR0B, RXEN0) : bit_reset(UCSR0B, RXEN0);
}

bool USART0::getReceivability() const {
    return bit_get(UCSR0B, RXEN0);
}

void USART0::setSendBufferInterruption(bool isEnable) const {
    isEnable ? bit_set(UCSR0B, UDRIE0) : bit_reset(UCSR0B, UDRIE0);
}

void USART0::setReceiveInterruption(bool isEnable) const {
    isEnable ? bit_set(UCSR0B, RXCIE0) : bit_reset(UCSR0B, RXCIE0);
}

}  // namespace usart

#endif
