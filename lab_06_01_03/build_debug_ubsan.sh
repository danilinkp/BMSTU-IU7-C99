#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer -fPIE -O0 -g -c main.c 
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer -fPIE -O0 -g -c product.c

clang main.o product.o -o app.exe -lm -fsanitize=undefined