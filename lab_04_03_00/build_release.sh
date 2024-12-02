#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -Wvla -c -O3 main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c -Wvla -c -O3 my_string.c

gcc main.o my_string.o -o app.exe -lm