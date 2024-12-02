#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -fsanitize=address -fno-omit-frame-pointer -O0 -g -c main.c 
clang main.o -o app.exe -lm -fsanitize=address