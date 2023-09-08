//
// UARTインタフェース 基底クラス
//
#ifndef UART_BASE_H
#define UART_BASE_H

#include <avr/pgmspace.h>
#include <stdint.h>

#include "buffer.hpp"
#include "registermap.hpp"

namespace uart {

constexpr buffer_size_t uartBufferSize = 32;

/**
 * @brief UARTインタフェース 基底クラス
 */
class UART final {
   private:
    uint8_t internalSendBufferDataPointer[uartBufferSize] = {0};
    uint8_t internalRecvBufferDataPointer[uartBufferSize] = {0};

    /**
     * @brief 内部送信バッファ
     */
    Buffer<uint8_t> internalSendBuffer;

    /**
     * @brief 内部受信バッファ
     */
    Buffer<uint8_t> internalRecvBuffer;

    /**
     * @brief レジスタマップ
     */
    const UARTRegisterMap registerMap;

    /**
     * @brief 送信バッファに書き込めるようになるまで待つ
     */
    void waitForSendBufferAvailable() const;

    /**
     * @brief ボーレート設定
     *
     * @param baudrate 構成するボーレート
     */
    void setBaudRate(const uint64_t&) const;

    /**
     * @brief UART送信許可設定
     *
     * @param isEnable 有効/無効
     */
    void setSendability(bool) const;

    /**
     * @brief UART送信許可状態取得
     *
     * @return bool
     */
    bool getSendability() const;

    /**
     * @brief UART受信許可設定
     *
     * @param isEnable 有効/無効
     */
    void setReceivability(bool) const;

    /**
     * @brief UART受信許可状態取得
     *
     * @return bool
     */
    bool getReceivability() const;

    /**
     *
     * @brief 送信バッファempty割り込みの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    void setSendBufferInterruption(bool) const;

    /**
     * @brief 受信割り込みの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    void setReceiveInterruption(bool) const;

   public:
    // -- constructor, destructor

    UART() = delete;
    explicit UART(const UARTRegisterMap& registerMap) : internalSendBuffer(internalSendBufferDataPointer, uartBufferSize),
                                                        internalRecvBuffer(internalRecvBufferDataPointer, uartBufferSize),
                                                        registerMap(registerMap){};

    // -- initialize

    /**
     * @brief UARTインタフェース初期化
     *
     * @param baudrate 設定するボーレート
     */
    void begin(const uint64_t& baudrate) const;

    // -- simple read/write

    /**
     * @brief UARTインタフェースへの出力
     *
     * @param data 書き込むデータ
     * @return size_t 書き込んだバイト数
     * @note この関数は内部送信バッファが空くまでブロックします。
     */
    size_t write(const uint8_t data);
    size_t write(const char* const data);

    /**
     * @brief 単一バイト読み込み
     *
     * @param data 結果を格納するバッファ
     * @return bool 受信バッファに値がない場合はfalseが返ります。またその場合 *data は変化しません。
     */
    bool read(uint8_t* const data);

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
     */
    size_t println(const char* const str);

    /**
     * @brief 文字列書き込み (プログラムメモリに保存されている文字を読み出す)
     *
     * @param str 書き込む文字列
     * @return size_t 実際に書き込んだ文字数
     */
    size_t print_P(PGM_P flashstr);

    size_t println_P(PGM_P flashstr);

    // -- high-level output

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

    size_t println(unsigned char value);
    size_t println(int value);
    size_t println(unsigned int value);
    size_t println(double value);
    size_t println(long value);
    size_t println(unsigned long value);

    // -- Interrupt functions

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

}  // namespace uart

#endif
