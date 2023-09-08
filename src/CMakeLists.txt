#
# avr-serial
#
cmake_minimum_required(VERSION 3.0)

add_library(uart)
target_sources(uart PRIVATE
    base.cpp
    interrupt.cpp
    initialize.cpp
    readwrite.cpp
    print.cpp
)
target_include_directories(uart PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(uart PUBLIC
    m
    printf_flt
)
target_compile_options(uart PRIVATE
    -Wall
)
target_link_options(uart PUBLIC
    -Wl,-u,vfprintf
)
