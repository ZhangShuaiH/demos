#!/bin/bash
# Created Time: 2020-04-28 17:41:25

set -ex
cd `dirname $0`
g++ -O0 main.cpp
./a.out
