#
# 小規模バッファ
#
cmake_minimum_required(VERSION 3.0)

add_library_avr(buffer)
target_include_directories(buffer PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
target_sources(buffer PRIVATE
    buffer.cpp
)
target_compile_options(buffer PRIVATE
    -Wall
)
