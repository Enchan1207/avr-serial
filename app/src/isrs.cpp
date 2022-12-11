//
// ISR定義
//
#include <avr/interrupt.h>

#include "usart.h"

/**
 * 送信バッファ空き
 */
ISR(USART_UDRE_vect) {
    usart.onUDREmpty();
}
