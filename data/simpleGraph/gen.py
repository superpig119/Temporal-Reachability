#!/usr/bin/python

import random

data = open('data10000', 'w')

nnode=9000
r=random

data.write(str(nnode) + '\n')

list = range(nnode)
for id in range(nnode):
	line = str(id)
	enum = r.randint(2, 10)
	line += '\t' + str(enum)
	slice = r.sample(list, enum)
	slice.sort()
	for e in slice:
		line += '\t' + str(e)
	line += '\n'
	data.write(line)

data.close()

