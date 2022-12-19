//
// 小規模バッファ
//
#include "buffer.h"

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
    // バッファがいっぱい(tailの次 = head)なら、戻る
    const buffer_size_t nextTail = (tail + 1) & (internalDataSize - 1);
    if (nextTail == head) {
        return BufferResult::Overflow;
    }

    // tailの位置にデータを書き込む
    *(internalData + tail) = data;

    // tailを進める
    tail = nextTail;

    return BufferResult::Success;
}

template <typename Element>
BufferResult Buffer<Element>::pop(Element* const data) {
    // バッファが空(tail = head)なら、戻る
    if (head == tail) {
        return BufferResult::Empty;
    }

    // 読み出して渡す
    *data = *(internalData + head);

    // headを進める
    head = (head + 1) & (internalDataSize - 1);

    return BufferResult::Success;
}

template class Buffer<uint8_t>;
