#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -Wvla -c -O3 main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -Wvla -c -O3 matrix.c

gcc main.o matrix.o -o app.exe -lm