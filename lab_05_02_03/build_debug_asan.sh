#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=address -fno-omit-frame-pointer -O0 -g -c main.c
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=address -fno-omit-frame-pointer -O0 -g -c file_tools.c


clang main.o file_tools.o -o app.exe -lm -fsanitize=address