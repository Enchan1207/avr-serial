//
// USARTインタフェース (リッチな型変換)
//
#include "usart.h"

size_t USART::print(const char* const str) {
    return write(str);
}

size_t USART::print(unsigned char value) {
    const size_t bufferSize = 8;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%d", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t USART::print(int value) {
    const size_t bufferSize = 16;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%d", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t USART::print(unsigned int value) {
    const size_t bufferSize = 16;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%u", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t USART::print(double value) {
    const size_t bufferSize = 32;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%lf", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t USART::print(long value) {
    const size_t bufferSize = 32;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%ld", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t USART::print(unsigned long value) {
    const size_t bufferSize = 32;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%lu", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t USART::println(const char* const str) {
    return write(str) + write("\r\n");
}

size_t USART::println(unsigned char value) {
    return print(value) + write("\r\n");
}

size_t USART::println(int value) {
    return print(value) + write("\r\n");
}

size_t USART::println(unsigned int value) {
    return print(value) + write("\r\n");
}

size_t USART::println(double value) {
    return print(value) + write("\r\n");
}

size_t USART::println(long value) {
    return print(value) + write("\r\n");
}

size_t USART::println(unsigned long value) {
    return print(value) + write("\r\n");
}
