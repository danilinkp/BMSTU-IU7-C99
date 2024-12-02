#!/bin/bash

./clean.sh

./build_debug.sh
cd func_tests/scripts/ || exit 1


./func_tests.sh

cd ..
cd ..
echo 
echo "Result of gcov:"
./collect_coverage.sh
./clean.sh