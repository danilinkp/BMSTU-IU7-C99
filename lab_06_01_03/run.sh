#!/bin/bash

./clean.sh

echo "Test result:"
./build_debug.sh
cd func_tests/scripts/ || exit 1


./func_tests.sh

cd ..
cd ..
echo 
echo "Result of coverage:"
./collect_coverage.sh
./clean.sh