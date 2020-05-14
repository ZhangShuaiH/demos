#!/bin/bash
# Created Time: 2020-04-24 11:03:08

set -xe

cd `dirname $0`
g++ -O0 main.cpp
./a.out
