#!/bin/bash

if [ $# -lt 2 ]; then
	exit 1
fi

file_in=$1
out_expect=$2
out_prog="out.txt"
app="../../app.exe"

$app < "$file_in" > $out_prog
error="$?"

if ! [ "$error" -eq 0 ]; then
	exit 1
fi

if ! ./comparator.sh "$out_prog" "$out_expect"; then
	exit 1
else
	exit 0
fi