//
// USARTインタフェース(抽象基底クラス)
//
#ifndef _USART_BASE_H_
#define _USART_BASE_H_

#include <stddef.h>
#include <stdint.h>

#include "buffer.h"

namespace usart {

constexpr buffer_size_t usartBufferSize = 32;

/**
 * @brief 非同期シリアル通信インタフェース 抽象基底クラス
 */
class BaseUSART {
   private:
    uint8_t internalSendBufferDataPointer[usartBufferSize] = {0};
    uint8_t internalRecvBufferDataPointer[usartBufferSize] = {0};

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
    volatile uint8_t* const dataRegister;

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
    virtual void setBaudRate(const uint64_t&) const = 0;

    /**
     * @brief USARTインタフェースの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    virtual void setComuunicatability(bool) const = 0;

    /**
     * @brief 送信バッファempty割り込みの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    virtual void setSendBufferInterruption(bool) const = 0;

    /**
     * @brief 受信割り込みの有効化/無効化
     *
     * @param isEnable 有効/無効
     */
    virtual void setReceiveInterruption(bool) const = 0;

   public:
    explicit BaseUSART(volatile uint8_t* const dataRegister) : internalSendBuffer(internalSendBufferDataPointer, usartBufferSize),
                                                               internalRecvBuffer(internalRecvBufferDataPointer, usartBufferSize),
                                                               dataRegister(dataRegister){};
    virtual ~BaseUSART() = default;

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

    /**
     * @brief 演算子newのオーバライド
     *
     * @note USART0を動的オブジェクトとして初期化することはできません。
     */
    void* operator new(size_t) = delete;

    /**
     * @brief 演算子deleteのオーバライド
     *
     * @note 対応する演算子newが存在しないため、この関数は何もせずに返ります。 コンパイル時のエラーを抑制するための実装です。
     */
    void operator delete(void*) noexcept __attribute__((weak)) {
        /* don't have to do anything because operator new is deleted */
    }
};

}  // namespace usart

// BaseUSARTは純粋仮想デストラクタを持つので、この子たちはどこかに定義しておかないといけない
// usart.hでは abi.cppにて stdlib.hの関数abortを呼ぶようにしています
extern "C" {
void __cxa_pure_virtual(void);
void __cxa_deleted_virtual(void) __attribute__((weak, noreturn));
}

#endif
