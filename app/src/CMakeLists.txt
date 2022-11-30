#
# SerialComm
#
cmake_minimum_required(VERSION 3.0)

add_executable_avr(main)
target_sources(main PRIVATE
    main.cpp
)
target_compile_options(main PRIVATE
    -Wall
)
