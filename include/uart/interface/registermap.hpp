//
// 　UARTペリフェラルレジスタマップ
//
#ifndef UART_REGISTER_MAP_H
#define UART_REGISTER_MAP_H

#include <stdint.h>

namespace uart {

/**
 * @brief レジスタマップ
 */
struct UARTRegisterMap {
    // データレジスタ
    volatile uint8_t* const data;

    // ボーレートレジスタ上位
    volatile uint8_t* const baudrateHigh;

    // ボーレートレジスタ下位
    volatile uint8_t* const baudrateLow;

    // 制御レジスタA
    volatile uint8_t* const stateAndControlA;

    // 制御レジスタB
    volatile uint8_t* const stateAndControlB;

    // 送信可能ビット
    const uint8_t txEnableBitPos;

    // 受信可能ビット
    const uint8_t rxEnableBitPos;

    // 倍速許可ビット
    const uint8_t doubleSpeedEnableBitPos;

    // 送信バッファ空き割込み許可ビット
    const uint8_t txInterruptEnableBitPos;

    // 受信割込み許可ビット
    const uint8_t rxInterruptEnableBitPos;
};

}  // namespace uart

#endif /* _UART_REGISTER_MAP_H_ */
