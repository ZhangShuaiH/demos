#!/bin/bash
# Created Time: 2020-04-08 09:58:59
set -e
if [ $# != 1 ];then 
	echo please add a log!
	echo -e "\texample: $0 'log text...'"
	exit 1
fi
set -x
git add .
git commit -m"$1"
git push
git status
