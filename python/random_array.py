import os, random

size = 20
min = 5
max = 100

file_name = __file__.split('\\')[-1][:-2]+'txt'
file = open(file_name, 'w')

array = []
for i in range(size):
    array.append(random.randint(min, max))
file.write(str(array))
    
    
