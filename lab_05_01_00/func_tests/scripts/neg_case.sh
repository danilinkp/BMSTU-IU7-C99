#!/bin/bash

if [ $# -lt 1 ]; then
	exit 1
fi

if [ $# -eq 2 ]; then
	out_test=$2
fi

file_in=$1
file_out="out.txt"
app="../../app.exe"

if [ $# -eq 3 ]; then
  file_arg=$3
	app="app $(cat "$file_arg")"
fi



$app < "$file_in" > $file_out
error="$?"

if [ "$error" -eq 0 ]; then
	exit 1
else
	if [ $# -eq 2 ]; then
		if ! ./comparator.sh "$file_out" "$out_test"; then
			exit 1
		else
			exit 0
		fi
	else
		exit 0
	fi
fi

