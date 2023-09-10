#!/usr/bin/env python3
#
# エコーバックチェック
#
import argparse
import random
import select
import socket
import subprocess
import sys


def main() -> int:
    # QEMUに渡すオプションとその他オプションをまとめて受け取る
    parser = argparse.ArgumentParser(prog="capture")
    parser.add_argument("--machine", "-M", required=True)
    parser.add_argument("-bios", required=True)
    args = parser.parse_args()

    # ソケットサーバをたてる
    server_address = ('localhost', 61092)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind(server_address)
        server_socket.listen()

        # 引数とオプションを整理してQEMU起動
        qemu_avr = "qemu-system-avr"
        machine = args.machine
        elf_path = args.bios
        subprocess_args = [qemu_avr, "-M", machine, "-bios", elf_path, "-nographic", "-serial",
                           f"tcp:{server_address[0]}:{server_address[1]},server=off"]
        process = subprocess.Popen(args=subprocess_args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

        # サーバはQEMUクライアントからの接続を受け付ける
        client_socket, _ = server_socket.accept()

        # ソケットにデータを投げ、同じデータが返る(エコーバックされる)ことを確認
        failed = False
        for data in range(0, 0x100, 16):
            # インジケータ
            print(".", end="", flush=True)

            # 16byteのバイト列をシャッフルして送信
            frame = list(range(data, data + 16))
            random.shuffle(frame)
            frame_bytes = bytes(frame)
            client_socket.send(frame_bytes)

            # 受信待ち
            timedout = False
            response: bytes = b''
            while len(response) < 16:
                rl, _, _ = select.select([client_socket], [], [], 2)
                if len(rl) == 0:
                    timedout = True
                    break
                response += client_socket.recv(16)

            # タイムアウトしたらエラー終了
            if timedout:
                print("error: socket timed out")
                failed = True
                break

            # レスポンスとフレームを比較
            if frame_bytes != response:
                print("packet mismatch:")
                print(f"source  : {frame_bytes.hex()}")
                print(f"response: {response.hex()}")
                failed = True
                break

        print()
        client_socket.close()

    # "q\n" を送信してQEMUを終了
    try:
        process.communicate(b'q\n')
    except:
        process.kill()
        return 1

    # 結果を返す
    return failed


if __name__ == "__main__":
    sys.exit(main())
