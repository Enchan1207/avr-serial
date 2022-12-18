#
# SerialComm
#
cmake_minimum_required(VERSION 3.0)

add_subdirectory(buffer)
add_subdirectory(usart)

add_executable_avr(main)
target_include_directories(main PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
target_sources(main PRIVATE
    main.cpp
    isrs.cpp
)
target_link_libraries(main
    usart
)
target_compile_options(main PRIVATE
    -Wall
)
