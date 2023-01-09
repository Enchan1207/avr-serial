#
# SerialComm
#
cmake_minimum_required(VERSION 3.0)

# load AVR toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/avr_toolchain.cmake")

# configure MCU
set(AVR_MCU "atmega328p")
set(AVRDUDE_MCU "m328p")
# set(AVR_MCU "attiny2313")
# set(AVRDUDE_MCU "t2313")
# set(AVR_MCU "atmega2560")
# set(AVRDUDE_MCU "m2560")
set(AVR_FCPU 16000000)

# configure programmer
set(AVRDUDE_PROGRAMMER "avrisp")
set(AVRDUDE_BAUDRATE 19200)

# Project configuration
project(SerialComm
    VERSION 0.1.0
    DESCRIPTION "serial (USART) communication"
    LANGUAGES C CXX
)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# source directory
add_subdirectory(src)
