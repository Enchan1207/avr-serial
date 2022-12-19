//
// 小規模バッファ
//

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <limits.h>
#include <stdint.h>

/**
 * @brief バッファ操作結果
 */
enum class BufferResult {
    Success,
    Overflow,
    Empty
};

/**
 * @brief バッファサイズを管理する変数の型
 */
using buffer_size_t = uint16_t;

/**
 * @brief 小規模バッファ
 *
 * @tparam Element 扱う要素の型
 */
template <typename Element>
class Buffer {
   private:
    /**
     * @brief 内部データ管理領域
     */
    Element* const internalData;

    /**
     * @brief 内部データ長さ
     */
    buffer_size_t internalDataSize;

    /**
     * @brief バッファ先頭
     */
    buffer_size_t head = 0;

    /**
     * @brief バッファ末尾
     */
    buffer_size_t tail = 0;

   public:
    /**
     * @brief 内部データを扱う領域とそのサイズを指定してバッファを初期化
     *
     * @param data 内部データ保管用領域
     * @param dataSize 領域サイズ
     * @note 領域サイズは2の冪乗であるべきです。それ以外の値を指定した場合、2の冪数のうち領域のサイズを下回らない最大のものが選択されます(15 -> 8, 34 -> 32).
     */
    Buffer(Element* const data, const buffer_size_t& dataSize);

    ~Buffer() = default;

    /**
     * @brief バッファにデータを追加
     *
     * @param data 追加するデータ
     * @return BufferResult 操作結果
     */
    BufferResult append(const Element& data);

    /**
     * @brief バッファからデータを取り出し
     *
     * @param data 取り出したデータの格納先
     * @return BufferResult 操作結果
     */
    BufferResult pop(Element* const data);

    /**
     * @brief バッファがいっぱいかどうか
     *
     * @return bool いっぱいならtrue、空きがあればfalse
     */
    bool isFull() const {
        const buffer_size_t nextTail = (tail + 1) & (internalDataSize - 1);
        return nextTail == head;
    }

    /**
     * @brief バッファが空かどうか
     *
     * @return bool 空ならtrue、データが存在すればfalse
     */
    bool isEmpty() const {
        return head == tail;
    }
};

template <typename Element>
Buffer<Element>::Buffer(Element* const data, const buffer_size_t& dataSize) : internalData(data) {
    // バッファサイズ型のビット数
    const uint8_t bufferSizeBitLength = sizeof(buffer_size_t) * CHAR_BIT;

    // 上からビットを立てていって、dataSizeとのANDで初めて非ゼロとなる値が最大値
    for (uint8_t i = bufferSizeBitLength - 1; i > 0; i--) {
        const buffer_size_t candidate = 1 << i;
        if ((candidate & dataSize) == 0) {
            continue;
        }

        internalDataSize = candidate;
        break;
    }
};

template <typename Element>
BufferResult Buffer<Element>::append(const Element& data) {
    // バッファがいっぱいなら戻る
    if (isFull()) {
        return BufferResult::Overflow;
    }

    // tailの位置にデータを書き込む
    *(internalData + tail) = data;

    // tailを進める
    tail = (tail + 1) & (internalDataSize - 1);

    return BufferResult::Success;
}

template <typename Element>
BufferResult Buffer<Element>::pop(Element* const data) {
    // バッファが空なら戻る
    if (isEmpty()) {
        return BufferResult::Empty;
    }

    // 読み出して渡す
    *data = *(internalData + head);

    // headを進める
    head = (head + 1) & (internalDataSize - 1);

    return BufferResult::Success;
}

#endif
