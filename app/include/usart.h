//
// USARTインタフェース
//
#ifndef _USART_H_
#define _USART_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"

constexpr buffer_size_t internalUSARTBufferSize = 32;

/**
 * @brief 非同期シリアル通信インタフェース
 */
class USART {
   private:
    uint8_t internalSendBufferDataPointer[internalUSARTBufferSize] = {0};
    uint8_t internalRecvBufferDataPointer[internalUSARTBufferSize] = {0};

    /**
     * @brief 内部送信バッファ
     */
    Buffer<uint8_t> internalSendBuffer;

    /**
     * @brief 内部受信バッファ
     */
    Buffer<uint8_t> internalRecvBuffer;

    /**
     * @brief USARTデータレジスタ
     */
    volatile uint8_t* udr;

    /**
     * @brief USART制御レジスタA
     */
    volatile uint8_t* ucsra;

    /**
     * @brief USART制御レジスタB
     */
    volatile uint8_t* ucsrb;

    /**
     * @brief USARTボーレート構成レジスタ
     */
    volatile uint16_t* ubrr;

    /**
     * @brief 送信バッファに書き込めるようになるまで待つ
     */
    void waitForSendBufferAvailable() const {
        // 送信バッファ割り込みを有効化 (無限ループ防止)
        setSendBufferInterruption(true);

        // 待機
        volatile bool isFull = internalSendBuffer.isFull();
        while (isFull) {
            isFull = internalSendBuffer.isFull();
        }
    }

    /**
     * @brief ボーレート設定
     *
     * @param baudrate 構成するボーレート
     */
    void setBaudRate(const uint64_t& baudrate) const;

    /**
     * @brief USARTインタフェースの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    void setComuunicatability(bool isEnable) const;

    /**
     * @brief 送信バッファempty割り込みの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    void setSendBufferInterruption(bool isEnable) const;

    /**
     * @brief 受信割り込みの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    void setReceiveInterruption(bool isEnable) const;

   public:
    USART(volatile uint8_t* udr,
          volatile uint8_t* ucsra,
          volatile uint8_t* ucsrb,
          volatile uint16_t* ubrr) : internalSendBuffer(internalSendBufferDataPointer, internalUSARTBufferSize), internalRecvBuffer(internalRecvBufferDataPointer, internalUSARTBufferSize), udr(udr), ucsra(ucsra), ucsrb(ucsrb), ubrr(ubrr){};
    ~USART() = default;

    // コピーコンストラクタの呼び出しを禁止
    USART(const USART&) = delete;
    USART& operator=(const USART&) = delete;

    // ムーブコンストラクタは呼び出し可能とする
    USART(USART&&) = default;
    USART& operator=(USART&&) = default;

    /**
     * @brief USARTインタフェース初期化
     *
     * @param baudrate 設定するボーレート
     */
    void begin(const uint64_t& baudrate) const;

    /**
     * @brief USARTインタフェースへの出力
     *
     * @param data 書き込むデータ
     * @return size_t 書き込んだバイト数
     * @note この関数は内部送信バッファが空くまでブロックします。
     */
    size_t write(const uint8_t data);
    size_t write(const char* const data);

    /**
     * @brief 文字列書き込み
     *
     * @param str 書き込む文字列
     * @return size_t 実際に書き込んだ文字数
     * @note 送信バッファが満杯の場合は、バッファが空くまでブロックします。
     */
    size_t print(const char* const str);

    /**
     * @brief 文字列書き込み(末尾に改行を追加)
     *
     * @param str 書き込む文字列
     * @return size_t 実際に書き込んだ文字数
     * @note 送信バッファが満杯の場合は、バッファが空くまでブロックします。
     */
    size_t println(const char* const str);

    /**
     * @brief 数値書き込み
     *
     * @param value 書き込む数値
     * @return size_t 実際に書き込んだ文字数
     */
    size_t print(unsigned char value);
    size_t print(int value);
    size_t print(unsigned int value);
    size_t print(double value);
    size_t print(long value);
    size_t print(unsigned long value);

    /**
     * @brief 数値書き込み(末尾に改行を追加)
     *
     * @param value 書き込む数値
     * @return size_t 実際に書き込んだ文字数
     */
    size_t println(unsigned char value);
    size_t println(int value);
    size_t println(unsigned int value);
    size_t println(double value);
    size_t println(long value);
    size_t println(unsigned long value);

    /**
     * @brief 単一バイト読み込み
     *
     * @param data 結果を格納するバッファ
     * @return bool 受信バッファに値がない場合はfalseが返ります。またその場合 *data は変化しません。
     */
    bool read(uint8_t* const data);

    /**
     * @brief UDRレジスタ空割り込み
     *
     * @note ISRから呼ばれることを想定しています。送信バッファが空でなければUDRレジスタへの書き込みを行います。
     */
    void onSendBufferEmpty();

    /**
     * @brief 受信割り込み
     *
     * @note ISRから呼ばれることを想定しています。受信バッファが空でなければUDRレジスタからの読み出しを行います。
     */
    void onReceive();
};

extern USART usart;

#endif
