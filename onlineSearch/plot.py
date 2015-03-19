#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

file = open("coordinate")
lines = file.readlines()
#plt.figure(1)
ax1 = plt.subplot(111)
for line in lines:
    s = line.split();
    l = s[1] + " " + s[2]
    plt.plot(int(s[5]), int(s[6]), 'o', label = l)
#    plt.legend()
plt.show()  

#plt.plot([10, 20, 30])  
#plt.xlabel('tiems')  
#plt.ylabel('numbers')  
