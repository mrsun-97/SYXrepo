#!/bin/zsh

gcc 6.c -lm -O2 -o 6.out && ./6.out > data3.txt
ls -lh  data*.txt 
