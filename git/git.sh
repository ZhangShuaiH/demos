#!/bin/bash
# Created Time: 2020-04-06 12:55:26

git init
# local associate remote repository
git remote add origin url
# push and associate remote master branch
git push -u origin master
git status
# del, add or change file at local
git add/rm file 
# commit all changes to repository cache
git commit -m'mark' 
# push local commits to remote master branch
git push origin master
# pull remote master to local
git pull origin master


# force down remote to local
git reset --hard

# stage all added and changed files
git add .
# list note tree
git log --oneline --graph --decorate --all
git reflog
git log -2
# overload local changes
git checkout filename/globbing
# change color.ui
git config --global color.ui auto

# only show file change add or delete operations
git diff commitID --name-status
