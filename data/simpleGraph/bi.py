#!/usr/bin/python

import sys

nodeNum=int(sys.argv[1])

outfile = open("databi", 'w')
outstr = str(nodeNum) + "\n"
outfile.write(outstr)

A = [i for i in range(0,nodeNum/2)]
B = [i for i in range(nodeNum/2, nodeNum)]

for i in A:
	outstr = str(i) + "\t2\t"
	if i==0:
		outstr += str(B[0]) + "\t" + str(B[1]) + "\n"
	elif i == A[-1]:
		outstr += str(B[-2]) + "\t" + str(B[-1]) + "\n"
	else:
		outstr += str(B[i-1]) + "\t" + str(B[i+1]) + "\n"
	outfile.write(outstr)

for i in B:
	outstr = str(i) + "\t0\n"
	outfile.write(outstr)

outfile.close()
