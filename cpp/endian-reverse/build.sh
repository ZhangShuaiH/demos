#!/bin/bash
# Created Time: 2020-04-13 15:43:06

set -xe
g++ -O2 -I../include main.cpp && ./a.out
