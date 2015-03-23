#!/usr/bin/python

import random

data = open('data100', 'w')

nnode=100
tperiod=1000
r=random

data.write(str(nnode) + '\n')

list = range(nnode)
for id in range(nnode):
	line = str(id)
	enum = r.randint(4, 10)
	slice = r.sample(list, enum)
	slice.sort()
	line += '\t' + str(enum)
	for e in slice:
		t1 = r. randint(1, tperiod)
		t2 = r. randint(1, tperiod)
		while t1 == t2:
			t1 = r. randint(1, tperiod)
			t2 = r. randint(1, tperiod)
		if(t1 > t2):
			tmp = t1
			t1 = t2
			t2 = tmp
		line += '\t' + str(e) + '\t' + str(t1) + '\t' + str(t2)
	line += '\n'
	data.write(line)

data.close()

