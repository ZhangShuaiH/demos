# utf-8
import os
import time

def get_absolute_paths(path):
    res = []
    for root, dirs, files in os.walk(path):
        for f in files:
            full_path = os.path.join(root, f)
            res.append(full_path)
    res.reverse()

    return res
    
if __name__ == '__main__':
    path = os.getcwd()
    paths = get_absolute_paths(path)
    str = ''
    for p in paths:
        str = str+p+'\n'
    file_name = __file__.split('\\')[-1][:-2]+'txt'
    file = open(file_name, 'w')
    file.write(str)
    file.close()
