#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

coordinate = open("coordinate")
lines = coordinate.readlines()
#plt.figure(1)
nodes = {}
ax1 = plt.subplot(111)
for line in lines:
    s = line.split();
    l = s[1] + " " + s[2]
	node[]
    plt.plot(int(s[5]), int(s[6]), 'o', label = l)
#    plt.legend()
plt.show()  

