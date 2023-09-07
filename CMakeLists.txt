#
# avr-serial
#
cmake_minimum_required(VERSION 3.0)

# Configure AVR toolchain
include(FetchContent)
FetchContent_Declare(
    avr_toolchain
    GIT_REPOSITORY https://github.com/Enchan1207/cmake-avr
    GIT_TAG v0.2.0
)
FetchContent_Populate(avr_toolchain)
set(CMAKE_TOOLCHAIN_FILE "${avr_toolchain_SOURCE_DIR}/cmake/avr_toolchain.cmake")

# Project configuration
project(avr-serial
    VERSION 0.1.0
    DESCRIPTION "UART interface library for AVR microcontroller"
    LANGUAGES C CXX
)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# source directory
add_subdirectory(src)
