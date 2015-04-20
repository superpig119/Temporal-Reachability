#!/usr/bin/python

import sys

filename = sys.argv[1]

infile=open(filename)
lines = infile.readlines()


op = open("data" + filename, 'w')
op.write(str(len(lines) - 3) + '\n')

i = 0
for line in lines:
    i += 1
    if i < 4:
        continue
    item = line.split()
    s = item[0] + '\t' + str(len(item) - 1)
    del item[0]
    item.sort()
    for t in item:
        s += '\t' + t
    s += '\n'
    op.write(s)

op.close()
infile.close()
