#!/bin/bash

if [ $# -lt 1 ]; then
	exit 1
fi

file_in=$1
file_out="out.txt"
app="./app.exe"

if [ $# -eq 2 ]; then
	app="$app $(cat "$2")"
	$app > $file_out
  error="$?"
else
  $app "$file_in" > $file_out
  error="$?"
fi

if [ "$error" -eq 0 ]; then
	exit 1
fi
exit 0

