#!/bin/bash

tmp_files="*.exe *.o *.gcov *.gcno *.gcda out.txt"

for file in $tmp_files; do
  rm -f "$file"
done
