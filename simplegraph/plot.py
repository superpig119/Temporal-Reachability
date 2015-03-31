#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.lines import Line2D 

coordinate = open("coordinate")
edgefile = open("edges")
nodes = coordinate.readlines()
edges = edgefile.readlines()
nodeinfo = {}

for line in nodes:
    s = line.split()
    nodeinfo[int(s[0])] = [int(s[1]), int(s[2])]
    plt.plot(int(s[1]), int(s[2]), 's')

for edge in edges:
    s = edge.split()
    plt.plot([nodeinfo[int(s[0])][0], nodeinfo[int(s[1])][0]], [nodeinfo[int(s[0])][1], nodeinfo[int(s[1])][1]], 'b')

plt.show()  
