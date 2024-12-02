#!/bin/bash

gcov main.c
echo --------
gcov product.c
echo --------
echo The coverage check is over