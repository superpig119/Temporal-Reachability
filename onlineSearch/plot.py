#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

coordinate = open("coordinate")
edgefile = open("edges")
nodes = coordinate.readlines()
edges = edgefile.readlines()
#plt.figure(1)
nodeinfo = {}
ax1 = plt.subplot(111)
for line in nodes:
    s = line.split()
    l = s[1] + " " + s[2]
	nodeinfo[int(s[3])] = [int(s[1]), int(s[2])]
	plt.plot(int(s[5]), int(s[6]), 'o', label = l)
#    plt.legend()

for edge in edges:
	s = line.split()
	plt.lines.line2D(nodeinfo[s[0]][0], nodeinfo[s[0]][0])

plt.show()  

