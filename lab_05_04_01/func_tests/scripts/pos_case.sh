#!/bin/bash

#s="pos_05_out.bin"
#echo ${s::-3}

if [ $# -lt 2 ]; then
	exit 1
fi

file_in=$1
number_of_test=$(echo "$file_in" | sed 's/[^0-9]//g')
out_expect=$2
out_prog="out.txt"


app="./app.exe"
import_app="./app.exe ""import ""$file_in ""./func_tests/data/pos_""$number_of_test""_in.bin"
$import_app
if [ $# -eq 3 ]; then
  args=$(cat "$3")
  app="$app $args"
  key=${args:0:2}
  if [ "$key" == "sb" ]; then
    $app > $out_prog
    error="$?"
  elif [ "$key" == "fb" ]; then
    $app
    export_app="./app.exe ""export ""${out_expect::-3}bin ""$out_prog"
    $export_app
  elif [ "$key" == "db" ]; then
    $app
    export_app="./app.exe ""export ""func_tests/data/pos_""$number_of_test""_in.bin ""$out_prog"
    $export_app
  fi
  error="$?"
else
  $app "$file_in" > $out_prog
  error="$?"
fi



if ! [ "$error" -eq 0 ]; then
	exit 1
fi

if ! ./func_tests/scripts/comparator.sh "$out_prog" "$out_expect"; then
	exit 1
else
	exit 0
fi