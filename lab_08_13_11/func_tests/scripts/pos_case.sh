#!/bin/bash

if [ $# -lt 2 ]; then
	exit 1
fi

file_in=$2
out_expect=$1
out_prog="out/out.txt"
args="$(cat "$file_in")"
app="./app.exe ""$args ""$out_prog"

$app
error="$?"

if ! [ "$error" -eq 0 ]; then
	exit 1
fi

if ! ./func_tests/scripts/comparator.sh "$out_prog" "$out_expect"; then
	exit 1
else
	exit 0
fi