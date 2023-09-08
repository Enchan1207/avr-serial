#
# collection2 tests for AVR microcontroller
#
cmake_minimum_required(VERSION 3.0)

# AVR用テストターゲットジェネレータ
macro(add_test_target source_file_name)
    get_filename_component(target_name "${source_file_name}" NAME_WE)
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

# テストターゲットの構成
add_test_target(test_print.cpp)
