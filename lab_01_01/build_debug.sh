#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c -O0 -g3 --coverage main.c
gcc --coverage main.o -o app.exe -lm