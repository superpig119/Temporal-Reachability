#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.lines import Line2D 
import sys

filename = sys.argv[1]
acc = open(filename)
lines = acc.readlines()

x= []
y=[]
oldx = 0;
oldy = 0;
for line in lines:
	s = line.split()
	plt.plot(int(s[0]), float(s[1]), 's')
#	if oldx != 0:
#		plt.plot(oldx, int(s[0]), oldy, float(s[1]), 'b')
#	oldx = int(s[0])
#	oldy = float(s[1])
	x.append(int(s[0]))
	y.append(float(s[1]))
plt.plot(x,y)
plt.axis([0,200,0,60])

plt.show()

acc.close()
	
