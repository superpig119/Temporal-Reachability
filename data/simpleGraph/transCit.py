#!/usr/bin/python

infile = open('cit-HepPh.txt')

lines = infile.readlines()
dl={}
count = 0
transold = []
for line in lines:
    v = line.split()
    if int(v[0]) not in dl.keys():
        dl[int(v[0])] = []
        count += 1
        if count % 1000 == 0: 
            print "Read "+ str(count) + " nodes"
        if int(v[0]) not in transold:
			transold.append(int(v[0]))
        if int(v[1]) not in transold:
			transold.append(int(v[1]))
    dl[int(v[0])].append(int(v[1]))
infile.close()

print "Finish reading"



keys = dl.keys()
keys.sort()    

transold.sort()
print transold
trans = {}
count = 0
for key in transold:
	trans[key] = count
	count += 1

outfile = open('citegraph', 'w')
o = str(len(trans)) + '\n'
outfile.write(o)

print trans

newdl = {}
for key in trans:
	if key in keys:
		for item in dl[key]:
			item = trans[item]
		newdl[key] = dl[key]
	else:
		newdl[key] = []

newkeys = newdl.keys()
newkeys.sort()
for key in newkeys:
    o = str(key) + '\t' + str(len(newdl[key]))
    for neighbor in newdl[key]:
        o += '\t' + str(neighbor)
    o += '\n'
    outfile.write(o)

outfile.close()
