#
# avr-serial
#
cmake_minimum_required(VERSION 3.0)

#
# AVR toolchain configuration
#
include(FetchContent)
FetchContent_Declare(
    avr_toolchain
    GIT_REPOSITORY https://github.com/Enchan1207/cmake-avr
    GIT_TAG v0.2.0
)
FetchContent_Populate(avr_toolchain)
set(CMAKE_TOOLCHAIN_FILE "${avr_toolchain_SOURCE_DIR}/cmake/avr_toolchain.cmake")

#
# Project configuration
#
project(avr-serial
    VERSION 0.1.1
    DESCRIPTION "UART interface library for AVR microcontroller"
    LANGUAGES C CXX
)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# source directory
add_subdirectory(src)

#
# Testing configuration
#
option(AVR_SERIAL_BUILD_TESTS "Enable testing of avr-serial" OFF)
if(AVR_SERIAL_BUILD_TESTS)
    message(NOTICE "avr-serial: testing enabled")
    enable_testing()
    add_subdirectory(tests)
endif()
