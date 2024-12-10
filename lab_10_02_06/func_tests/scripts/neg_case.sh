#!/bin/bash

if [ $# -lt 1 ]; then
	exit 1
fi

file_in=$1
file_out="out.txt"
app="./app.exe"

if [ $# -eq 2 ]; then
	args=$(cat "$2")
  app="$app $args $file_in $file_out"
  $app
  error="$?"
else
  $app < "$file_in"
  error="$?"
fi

if [ "$error" -eq 0 ]; then
	exit 1
fi
exit 0

