#!/bin/bash

clang -std=c99 -fsanitize=undefined -fPIE -pie -fno-omit-frame-pointer -g -c main.c
clang main.o -o app.exe -lm