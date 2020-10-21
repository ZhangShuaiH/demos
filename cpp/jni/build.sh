#!/bin/bash
# Created Time: 2020-04-13 16:20:14

javac Main.java # 生成 class 文件

javah Main # 生成 Main.h

g++ -shared -fPIC main.cpp -o libmain.so # 生成 libmain.so 文件

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd` # 环境变量

java Main # 执行
