#
# avr-serial
#
cmake_minimum_required(VERSION 3.0)

add_library(usart)
target_sources(usart PRIVATE
    abi.cpp
    event.cpp
    initialize.cpp
    readwrite.cpp
    print.cpp

    usart0.cpp
    usart1.cpp
    usart2.cpp
    usart3.cpp
)
target_include_directories(usart PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(usart PUBLIC
    m
    printf_flt
)
target_compile_options(usart PRIVATE
    -Wall
)
target_link_options(usart PUBLIC
    -Wl,-u,vfprintf
)
