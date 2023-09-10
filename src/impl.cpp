//
// インタフェース具象実装
//
#include "uart/uart.hpp"

namespace uart {

#ifdef HAS_UART_0
UART Serial0({&UDR0, &UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, TXEN0, RXEN0, U2X0, UDRIE0, RXCIE0});
#endif

#ifdef HAS_UART_1
UART Serial1({&UDR1, &UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, TXEN1, RXEN1, U2X1, UDRIE1, RXCIE1});
#endif

#ifdef HAS_UART_2
UART Serial2({&UDR2, &UBRR2H, &UBRR2L, &UCSR2A, &UCSR2B, TXEN2, RXEN2, U2X2, UDRIE2, RXCIE2});
#endif

#ifdef HAS_UART_3
UART Serial3({&UDR3, &UBRR3H, &UBRR3L, &UCSR3A, &UCSR3B, TXEN3, RXEN3, U2X3, UDRIE3, RXCIE3});
#endif

}  // namespace uart
