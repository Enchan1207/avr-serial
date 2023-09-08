//
// UARTインタフェース (リッチな型変換)
//
#include <stdio.h>

#include "uart/interface/base.hpp"

namespace uart {

size_t UART::print(const char* const str) {
    return write(str);
}

size_t UART::print_P(PGM_P flashstr) {
    PGM_P currentStringPtr = flashstr;

    // 文字列の終端に当たるまで出力
    size_t writeCount = 0;
    char c = pgm_read_byte(currentStringPtr++);
    while (c != '\0') {
        write(c);
        writeCount++;
        c = pgm_read_byte(currentStringPtr++);
    }
    return writeCount;
}

size_t UART::print(unsigned char value) {
    const size_t bufferSize = 8;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%d", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t UART::print(int value) {
    const size_t bufferSize = 16;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%d", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t UART::print(unsigned int value) {
    const size_t bufferSize = 16;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%u", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t UART::print(double value) {
    const size_t bufferSize = 32;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%lf", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t UART::print(long value) {
    const size_t bufferSize = 32;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%ld", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t UART::print(unsigned long value) {
    const size_t bufferSize = 32;
    char buf[bufferSize] = {0};
    int writtenCharLength = snprintf(buf, bufferSize, "%lu", value);
    if (writtenCharLength < 0 || (size_t)writtenCharLength >= bufferSize) {
        return 0;
    }
    write(buf);
    return bufferSize;
}

size_t UART::println_P(PGM_P flashstr) {
    return print_P(flashstr) + print_P(PSTR("\r\n"));
}

size_t UART::println(const char* const str) {
    return print(str) + print_P(PSTR("\r\n"));
}

size_t UART::println(unsigned char value) {
    return print(value) + print_P(PSTR("\r\n"));
}

size_t UART::println(int value) {
    return print(value) + print_P(PSTR("\r\n"));
}

size_t UART::println(unsigned int value) {
    return print(value) + print_P(PSTR("\r\n"));
}

size_t UART::println(double value) {
    return print(value) + print_P(PSTR("\r\n"));
}

size_t UART::println(long value) {
    return print(value) + print_P(PSTR("\r\n"));
}

size_t UART::println(unsigned long value) {
    return print(value) + print_P(PSTR("\r\n"));
}

}  // namespace uart
