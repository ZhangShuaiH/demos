#!/bin/bash
# Created Time: 2020-04-24 11:03:08

set -xe

g++ -g main.cpp
./a.out
objdump -S a.out >log
