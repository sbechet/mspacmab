#!/bin/bash

# Sprites, Charset and Wave
(
gcc -o extract-sprites-and-charset extract-sprites-and-charset.c ; ./extract-sprites-and-charset
) > mspacmab_data.rs

convert -depth 8 -size 8x2048 gray:5e.ok mspacmab_tile.png
convert -depth 8 -size 16x1024 gray:5f.ok mspacmab_sprite.png
rm 5e.ok 5f.ok

# ROM and RAM binary
dd if=/dev/zero of=boot4_2_zero count=1 bs=16384
dd if=/dev/zero of=boot7_zero count=1 bs=24576
cat boot1 boot2 boot3 boot4 boot4_2_zero boot5 boot6 boot7_zero > mspacmab_romram.bytes
rm boot4_2_zero boot7_zero

