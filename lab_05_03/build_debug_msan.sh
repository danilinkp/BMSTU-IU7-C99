#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -fPIE -O0 -g -c main.c
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -fPIE -O0 -g -c file_tools.c
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -fPIE -O0 -g -c import.c
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fno-omit-frame-pointer -fPIE -O0 -g -c export.c

clang -fno-omit-frame-pointer -fPIE -fsanitize=memory main.o file_tools.o import.o export.o -o app.exe -lm