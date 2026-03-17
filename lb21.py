#!/usr/bin/env python3

import os
import sys
import argparse


def main():
    parser = argparse.ArgumentParser(
        description="Concatenate files from DIR until total size exceeds BLOCK_SIZE."
    )
    parser.add_argument("directory", help="source directory with input files")
    parser.add_argument("block_size", type=int, help="block size in bytes")
    parser.add_argument("output", nargs="?", default="concatenated.out",
                        help="resulting file (default: concatenated.out)")

    args = parser.parse_args()

    dir_path = args.directory
    block_size = args.block_size
    out_file = args.output

    if block_size <= 0:
        print("Error: BLOCK_SIZE must be positive")
        sys.exit(1)

    if not os.path.isdir(dir_path):
        print(f"Error: directory '{dir_path}' not found")
        sys.exit(2)

    # Получаем список файлов
    files = []
    for name in os.listdir(dir_path):
        path = os.path.join(dir_path, name)
        if os.path.isfile(path):
            files.append(path)

    files.sort()

    if not files:
        print(f"Error: no files in '{dir_path}'")
        sys.exit(3)

    # Очищаем выходной файл
    open(out_file, "w").close()

    total = 0
    count = 0

    with open(out_file, "ab") as out:
        for f in files:
            size = os.path.getsize(f)

            if total + size > block_size:
                break

            with open(f, "rb") as inp:
                out.write(inp.read())

            total += size
            count += 1

    print(f"Added {count} files to {out_file}")
    print(f"Total size: {total} bytes (block: {block_size} bytes)")
