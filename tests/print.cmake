#
# テストケース: 単純な文字の表示
#

# 出力アサーションを構成
macro(expect_output target_name message)
    target_compile_definitions(${target_name} PUBLIC MESSAGE=\"${message}\")
    add_test(NAME assert_${target_name} COMMAND ${PROJECT_SOURCE_DIR}/tests/capture.py -M ${qemu_machine_map_${AVR_MCU}} -bios ${target_name} --wait 1 --compare ${message})
endmacro()

# SRAMから短いメッセージを読み込む
add_test_target(test_print_sram_short test_print.cpp)
expect_output(test_print_sram_short "short message stored in SRAM")

# SRAMから長いメッセージを読み込む
add_test_target(test_print_sram_long test_print.cpp)
expect_output(test_print_sram_long "Very long message stored in SRAM. UART transmission buffer has 32 bytes long, so it'll block until the transmission is complete.")

# Flashから短いメッセージを読み込む
add_test_target(test_print_flash_short test_print.cpp)
target_compile_definitions(test_print_flash_short PUBLIC READ_FROM_FLASH)
expect_output(test_print_flash_short "short message stored in Flash")

# Flashから長いメッセージを読み込む
add_test_target(test_print_flash_long test_print.cpp)
target_compile_definitions(test_print_flash_long PUBLIC READ_FROM_FLASH)
expect_output(test_print_flash_long "Very long message stored in Flash. UART transmission buffer has 32 bytes long, so it'll block until the transmission is complete.")
