//
// UARTインタフェース
//
#ifndef UART_UART_H
#define UART_UART_H

#include <avr/io.h>

#include "interface/base.hpp"

namespace uart {

// ターゲットが持つUARTインタフェースに対応するクラスのみを定義したいので、
// レジスタ定義の有無からI/Fの存在チェックを行う

#if defined(UBRRH) || defined(UBRR0H)

// レジスタ名ほかの表記揺れを吸収
#if defined(UDR) && !defined(UDR0)
#define UDR0 UDR
#define UBRR0H UBRRH
#define UBRR0L UBRRL
#define UCSR0A UCSRA
#define UCSR0B UCSRB
#define TXEN0 TXEN
#define RXEN0 RXEN
#define U2X0 U2X
#define UDRIE0 UDRIE
#define RXCIE0 RXCIE
#endif

// Serial0
UART Serial0({&UDR0, &UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, TXEN0, RXEN0, U2X0, UDRIE0, RXCIE0});
#define Serial Serial0

#endif

#if defined(UBRR1H)
// Serial1
UART Serial1({&UDR1, &UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, TXEN1, RXEN1, U2X1, UDRIE1, RXCIE1});
#endif

#if defined(UBRR2H)
// Serial2
UART Serial2({&UDR2, &UBRR2H, &UBRR2L, &UCSR2A, &UCSR2B, TXEN2, RXEN2, U2X2, UDRIE2, RXCIE2});
#endif

#if defined(UBRR3H)
// Serial3
UART Serial3({&UDR3, &UBRR3H, &UBRR3L, &UCSR3A, &UCSR3B, TXEN3, RXEN3, U2X3, UDRIE3, RXCIE3});
#endif

}  // namespace uart

#endif /* _UART_UART_H_ */
