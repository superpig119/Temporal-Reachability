#!/usr/bin/python

#Drawing the graph of False Positive ratio

import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.lines import Line2D 
import sys

fsize = 10000
fedge = 20
beta = [0.3, 0.5, 0.7, 0.9, 1]

#filename = sys.argv[1]
for b in beta:
	filename = str(fsize) + '/' + str(fedge) + "/" + str(b) + "/FPrate"
	FPfile = open(filename)
	lines = FPfile.readlines()
	x= []
	y=[]
	for line in lines:
		s = line.split()
		plt.plot(int(s[0]), float(s[1]), 's')
		x.append(int(s[0]))
		y.append(float(s[1]))
	plt.plot(x,y)	
	FPfile.close()

upperX = 200
upperY = 0.5

plt.axis([0,upperX,0,upperY])

plt.show()

	
