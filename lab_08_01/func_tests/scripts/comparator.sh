#!/bin/bash

if [ ! -f "$1" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Файл 1 не найден
    fi
    exit 2
fi
if [ ! -f "$2" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Файл 2 не найден
    fi
    exit 2
fi

if [ ! -r "$1" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Нет доступа к файлу 1
    fi
    exit 2
fi
if [ ! -r "$2" ]; then
    if echo "$3" | grep -Eq "^-v$"; then
        echo Нет доступа к файлу 2
    fi
    exit 2
fi

file1=$1
file2=$2

numbers_1=$(grep -Eo "Result: .*" "$file1")
numbers_2=$(grep -Eo "Result: .*" "$file2")


if [ "$numbers_1" != "$numbers_2" ]; then
    exit 1
fi

exit 0