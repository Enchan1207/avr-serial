#
# SerialComm
#
cmake_minimum_required(VERSION 3.0)

add_library_avr(usart)
target_include_directories(usart PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
target_sources(usart PRIVATE
    event.cpp
    initialize.cpp
    readwrite.cpp
    configure.cpp
    print.cpp
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
