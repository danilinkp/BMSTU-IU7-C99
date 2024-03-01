#!/bin/bash

if [ $# -lt 1 ]; then
	exit 1
fi

file_in=$1
file_out="out.txt"
app="../../app.exe"

$app < "$file_in" > $file_out

if [ $? ]; then
	exit 0
fi

exit 1
