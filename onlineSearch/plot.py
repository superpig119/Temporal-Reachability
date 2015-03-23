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
#ax1 = plt.subplot(111)
for line in nodes:
    s = line.split()
    l = s[1] + " " + s[2]
    nodeinfo[int(s[3])] = [int(s[5]), int(s[6])]
    if int(s[4])==0:
        plt.plot(int(s[5]), int(s[6]), 's', label = l)
    else:
        plt.plot(int(s[5]), int(s[6]), 'o', label = l)
#    plt.legend()
print nodeinfo

for edge in edges:
    s = edge.split()
    print edge
    print s[0], nodeinfo[int(s[0])], s[1], nodeinfo[int(s[1])]
#    plt.plot([1,3],[6,4])
#l = Line2D(nodeinfo[int(s[0])], nodeinfo[int(s[1])])
    if int(s[2])==0:
		plt.plot([nodeinfo[int(s[0])][0], nodeinfo[int(s[1])][0]], [nodeinfo[int(s[0])][1], nodeinfo[int(s[1])][1]], 'r--')
    else:
		plt.plot([nodeinfo[int(s[0])][0], nodeinfo[int(s[1])][0]], [nodeinfo[int(s[0])][1], nodeinfo[int(s[1])][1]], 'g')

plt.show()  
