#!/bin/bash
# Created Time: 2020-04-06 12:55:26

git init
# 添加远程仓库，别名为 origin
git remote add origin url
# 关联远程仓库
git push -u origin master
git status
# 将本地修改同步到index中
git add/rm file 
# 将修改同步到本地库
git commit -m'mark' 
# 将修改推送到远程库
git push origin master
# 同步远程库到本地
git pull origin master


# 强制同步远程库到本地
git reset --hard

# 提交本地添加或修改的文件
git add .
# 提交本地添加、修改或删除的文件
git add --all
# 图形化显示日志
git log --oneline --graph --decorate --all
git reflog
git log -2
# 覆盖本地修改的文件
git checkout filename/globbing
# change color.ui
git config --global color.ui auto

# 只显示修改删除添加的文件名称
git diff commitID --name-status
