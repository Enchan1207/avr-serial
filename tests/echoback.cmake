#
# テストケース: エコーバック
#

# エコーバック
add_test_target(test_echoback test_echoback.cpp)
add_test(NAME test_echoback COMMAND ${PROJECT_SOURCE_DIR}/tests/echoback.py -M ${qemu_machine_map_${AVR_MCU}} -bios test_echoback)
