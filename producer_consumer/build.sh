#!/bin/bash
# Created Time: 2020-04-24 11:03:08

set -xe

g++  main.cpp WholeSaler.cpp -lpthread
./a.out 
