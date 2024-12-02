#!/bin/bash

curr_path="*.sh"
scripts_path="func_tests/scripts/*.sh"

for script in $curr_path; do
  if [ -f "$script" ]; then
    shellcheck "$script"
  fi
done

for script in $scripts_path; do
  if [ -f "$script" ]; then
    shellcheck "$script"
  fi
done

exit 0