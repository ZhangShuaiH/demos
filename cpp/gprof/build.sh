#!/bin/bash
# Created Time: 2020-04-26 11:39:36

set -xe
g++ -pg main.cpp
./a.out
gprof a.out > res
