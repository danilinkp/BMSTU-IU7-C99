#!/bin/bash

rm -f "*.bin"

tmp_files="*.exe *.o *.gcov *.gcno *.gcda out.txt *.bin"

for file in $tmp_files; do
  rm -f "$file"
done