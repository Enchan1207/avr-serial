//
// USARTインタフェース
//
#ifndef _USART_H_
#define _USART_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

using buffer_size_t = uint16_t;
constexpr buffer_size_t internalUSARTBufferSize = 32;

/**
 * @brief 非同期シリアル通信インタフェース
 */
class USART {
   private:
    struct Buffer {
        buffer_size_t head = 0;
        buffer_size_t tail = 0;
        uint8_t rawData[internalUSARTBufferSize] = {0};
    };
    struct Buffer internalSendBuffer;
    struct Buffer internalRecvBuffer;

    /**
     * @brief writeの内部処理
     *
     * @param data 書き込むデータ
     * @return bool 処理結果
     */
    bool _write(const uint8_t data);

    /**
     * @brief printの内部処理
     *
     * @param str 書き込むデータ
     * @return size_t 実際に書き込めたbyte数
     */
    size_t _print(const char* const str);

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
    USART() = default;
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
     * @brief 単一バイト書き込み
     *
     * @param data 書き込むデータ
     * @return bool バッファが満杯等の理由で書き込みに失敗した場合はfalseが返ります。
     */
    bool write(const uint8_t data);

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
     * @note 暫定実装です。送信バッファが満杯の場合はデータを切り捨てます。
     */
    size_t print(const char* const str);

    /**
     * @brief 文字列書き込み(末尾に改行を追加)
     *
     * @param str 書き込む文字列
     * @return size_t 実際に書き込んだ文字数
     * @note 暫定実装です。送信バッファが満杯の場合はデータを切り捨てます。
     */
    size_t println(const char* const str);

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
