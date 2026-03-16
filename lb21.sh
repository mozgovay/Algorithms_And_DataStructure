#!/bin/bash

help() {
    echo "Usage: $0 DIR BLOCK_SIZE [OUTPUT_FILE]"
    echo
    echo "Concatenate files from DIR until total size exceeds BLOCK_SIZE."
    echo
    echo "Arguments:"
    echo "  DIR           source directory with input files"
    echo "  BLOCK_SIZE    block size in bytes"
    echo "  OUTPUT_FILE   resulting file (default: concatenated.out)"
    echo
    echo "Options:"
    echo "  -h, --help    show this help message"
}

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    help
    exit 0
fi

if [ $# -lt 2 ] || [ $# -gt 3 ]; then
    echo "Error: wrong number of arguments"
    help
    exit 1
fi

dir=$1
block_size=$2

if [ ! -d "$dir" ]; then
    echo "Error: directory '$dir' not found"
    exit 2
fi

if [ $# -eq 3 ]; then
    out=$3
else
    out="concatenated.out"
fi

files=$(ls "$dir" 2>/dev/null)
if [ -z "$files" ]; then
    echo "Error: no files in '$dir'"
    exit 3
fi

> "$out"

total=0
count=0

for f in "$dir"/*; do
    [ -f "$f" ] || continue
    
    size=$(stat -c%s "$f")
    
    if [ $((total + size)) -gt $block_size ]; then
        break
    fi
    
    cat "$f" >> "$out"
    total=$((total + size))
    count=$((count + 1))
done

echo "Added $count files to $out"
echo "Total size: $total bytes (block: $block_size bytes)"
