#!/bin/zsh

gcc 7.c -lm -O2 -o 7.out && ./7.out > data3.txt
ls -lh  data*.txt 
