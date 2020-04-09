# coding=utf-8
import os, io, re
from compiler.ast import flatten


# 读取配置文件
def readCfgFile():
    file = open('config.txt', 'r')
    lines = file.readlines();
    types = []
    paths = []
    for line in lines:
        if line[0]=='\n' or line[0]=='#' or line[0]==' ':
            continue
        
        if line[0]=='.':
            if line[-1]=='\n':
                line = line[:-1]
            types.append(line)
        else:
            if line[-1]=='\n':
                line = line[:-1]
            paths.append(line)
            
    return paths,types
    
# 递归获取文件夹下的所有文件的绝对路径
def rgetvalid_files_files(paths):
    res = []
    for path in paths:
        for i in os.walk(path):
            for fn in i[-1]:
                full_path = os.path.join(i[0], fn)
                res.append(full_path)
    res.reverse()

    return res

    
# 获取当前目录下的文件列表
def cwdvalid_files_files():
    path = os.getcwd()
    for i in os.walk(path):
        return i[2]
        break;


# 读取文件中的行数
def countLines(file):
    try:
        strfile = open(file, 'r')
        lines = strfile.readlines()
        strfile.close()
        lineCount = len(lines)
        return lineCount
    except:
        print('----------------open ' + file + ' error!')
    return 0
    
def main():
    print('fileNames and lineNumber\n')
    
    paths, types = readCfgFile()
    
    valid_files_files = rgetvalid_files_files(paths)

    valid_files = []
    for t in types:
        for f in valid_files_files:
            if re.match("(.*\\"+t+"$)", f):
                valid_files.append(f)
    
    sumLineCount = 0
    for f in valid_files:
        line_num = countLines(f)
        sumLineCount += line_num
        print(f + '\t' + str(line_num))
    print('\nall lines:'),
    print(sumLineCount)
    
if __name__ == '__main__':
    main()
