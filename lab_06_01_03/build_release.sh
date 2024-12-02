#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-conversion -Wvla -c -O3 main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-conversion -Wvla -c -O3 product.c

gcc main.o product.o -o app.exe -lm