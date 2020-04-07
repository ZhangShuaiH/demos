#!/bin/bash
# Created Time: 2020-04-05 23:26:11

set -xe

mkdir -p build 
cd build
cmake ..
make all
./main
