#!/bin/bash
# Created Time: 2020-04-24 11:03:08

set -xe

g++  2main.cpp WholeSaler.cpp -lpthread
time ./a.out 
