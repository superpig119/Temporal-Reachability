#!/usr/bin/python

import random

data = open('data20', 'w')

nnode=20
r=random

data.write(str(nnode) + '\n')

list = range(nnode)
for id in range(nnode):
	line = str(id)
	enum = r.randint(4, 10)
	line += '\t' + str(enum)
	slice = r.sample(list, enum)
	slice.sort()
	for e in slice:
		line += '\t' + str(e)
	line += '\n'
	data.write(line)

data.close()

