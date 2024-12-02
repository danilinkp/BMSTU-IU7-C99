#!/bin/bash

if [ $# -lt 1 ]; then
	exit 1
fi

file_in=$1
file_out="out.txt"
app="../../app.exe"

$app < "$file_in" > $file_out
error=$?

if [ $error -eq 0 ]; then
	exit 1
fi

exit 0
