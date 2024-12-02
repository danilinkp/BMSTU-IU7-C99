#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer -fPIE -O0 -g -c main.c 
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer -fPIE -O0 -g -c array.c 
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer -fPIE -O0 -g -c matrix.c 

clang main.o array.o matrix.o -o app.exe -lm -fsanitize=undefined