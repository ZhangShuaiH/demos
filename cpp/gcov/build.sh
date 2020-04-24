#!/bin/bash
# Created Time: 2020-04-13 18:52:10

set -e 

if [[ $# == 1 && $1 == rm ]];then
	rm -rf main.gcda main main.gcno main.info res
	exit 0
fi

g++ main.cpp -o main -ftest-coverage -fprofile-arcs
./main
lcov -c -o main.info -d .
#gcov -c -o main.info -d .
genhtml main.info -o res -s



