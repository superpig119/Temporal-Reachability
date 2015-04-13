#!/usr/bin/python

#Drawing the graph of Need Onlineserach ratio

import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.lines import Line2D 
import sys

filename = sys.argv[1]
acc = open(filename)
lines = acc.readlines()

upperX = 200
upperY = 0.5

x= []
y=[]
oldx = 0;
oldy = 0;
for line in lines:
	s = line.split()
	plt.plot(int(s[0]), float(s[1]), 's')
	x.append(int(s[0]))
	y.append(float(s[1]))
plt.plot(x,y)
plt.axis([0,upperX,0,upperY])

plt.show()

acc.close()
	
