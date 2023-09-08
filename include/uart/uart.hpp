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
#define HAS_UART_0

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
extern UART Serial0;
#define Serial Serial0

#endif

#if defined(UBRR1H)
#define HAS_UART_1
// Serial1
extern UART Serial1;
#endif

#if defined(UBRR2H)
#define HAS_UART_2
// Serial2
extern UART Serial2;
#endif

#if defined(UBRR3H)
#define HAS_UART_3
// Serial3
extern UART Serial3;
#endif

}  // namespace uart

#endif /* _UART_UART_H_ */
