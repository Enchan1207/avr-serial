#!/usr/bin/env python3
#
# 出力アサーション
#
import argparse
import subprocess
import sys
import time


def main() -> int:
    # QEMUに渡すオプションとその他オプションをまとめて受け取る
    parser = argparse.ArgumentParser(prog="capture")
    parser.add_argument("--machine", "-M", required=True)
    parser.add_argument("-bios", required=True)
    parser.add_argument("--compare", type=str, required=True)
    parser.add_argument("--wait", default=1, type=float)
    args = parser.parse_args()

    # 引数とオプションを整理
    qemu_avr = "qemu-system-avr"
    machine = args.machine
    elf_path = args.bios
    wait = args.wait
    subprocess_args = [qemu_avr, "-M", machine, "-bios", elf_path, "-nographic"]

    # プロセスを作成し、処理完了まで一定時間待機
    process = subprocess.Popen(args=subprocess_args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    time.sleep(wait)

    # QEMUに C-a x を送信し、終了させる
    try:
        process_output, errors = process.communicate(b'\x01x')
    except:
        process.kill()
        return 1

    if errors is not None:
        return 1

    # 得られた出力を文字列に変換し、最終行のQEMUが出力したメッセージ以降を削る
    qemu_fragment_index = process_output.rfind(b"QEMU: Terminated")
    if qemu_fragment_index == -1:
        return 1
    origin_output = process_output[:qemu_fragment_index]

    # 比較オプションが指定された場合は標準入力から読み込んで比較する
    if args.compare is None:
        return 1

    if args.compare.encode() != origin_output:
        print("FATAL: source and output values are not equal:")
        print(f"source: {args.compare}")
        print(f"output: {origin_output.decode()}")
        return 1

    # 指定されなければ標準出力に書き出す
    sys.stdout.buffer.write(origin_output)
    sys.stdout.buffer.flush()
    return 0


if __name__ == "__main__":
    sys.exit(main())
