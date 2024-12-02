#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-conversion -Wvla -c -O3 main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wfloat-conversion -Wvla -c -O3 file_tools.c

gcc main.o file_tools.o -o app.exe -lm