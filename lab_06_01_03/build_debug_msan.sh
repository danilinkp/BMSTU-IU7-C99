#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -fPIE -O0 -g -c main.c
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -fPIE -O0 -g -c product.c

clang -fno-omit-frame-pointer -fPIE -fsanitize=memory main.o product.o -o app.exe -lm