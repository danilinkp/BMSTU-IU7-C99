#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c -O3 main.c
gcc main.o -o app.exe -lm