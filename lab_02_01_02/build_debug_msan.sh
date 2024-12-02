#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -fPIE -O0 -g -c main.c 

clang main.o -o app.exe -lm -fsanitize=memory