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
    communicate.cpp
    configure.cpp
)
target_link_libraries(usart
    buffer
)
target_compile_options(usart PRIVATE
    -Wall
)
