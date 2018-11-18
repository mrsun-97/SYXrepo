#!/usr/bin/zsh

gcc 9.c -lm -O3 -o 9.out && ./9.out > data.txt
ls -lh data.txt
