#!/bin/bash
# Created Time: 2020-04-13 18:52:10

g++ main.cpp -o main -ftest-coverage -fprofile-arcs
./main
#lcov -c -o main.info -d .
gcov -c -o main.info -d .
genhtml main.info -o res -s
