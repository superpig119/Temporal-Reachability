#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.lines import Line2D 

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
print nodeinfo

for edge in edges:
	s = edge.split()
	print edge
	print nodeinfo[int(s[1])], nodeinfo[int(s[2])]
	l = Line2D(nodeinfo[int(s[0])], nodeinfo[int(s[1])])
	plt.gca().add_line(l)

plt.show()  

