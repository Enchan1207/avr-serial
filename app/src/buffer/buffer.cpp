//
// 小規模バッファ
//
#include "buffer.h"

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
