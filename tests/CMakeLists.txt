#
# collection2 tests for AVR microcontroller
#
cmake_minimum_required(VERSION 3.0)

# AVR用テストターゲットジェネレータ
macro(add_test_target target_name source_file_name)
    add_executable(${target_name})
    target_sources(${target_name} PRIVATE
        isrs.cpp
        ${source_file_name}
    )
    target_include_directories(${target_name} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    target_compile_options(${target_name} PRIVATE -Wall)
    target_link_libraries(${target_name} PRIVATE uart)
    target_configure_for_avr(${target_name})
endmacro()

# QEMUの -machine に渡す値と avr-gccの -mmcu に渡す値のマップ
set(qemu_machine_map_atmega168 arduino-duemilanove)
set(qemu_machine_map_atmega168p arduino-duemilanove)
set(qemu_machine_map_atmega328 arduino-uno)
set(qemu_machine_map_atmega328p arduino-uno)
set(qemu_machine_map_atmega1280 arduino-mega)
set(qemu_machine_map_atmega2560 arduino-mega-2560-v3)

# テストケースの定義をinclude
include(print.cmake)
include(echoback.cmake)
