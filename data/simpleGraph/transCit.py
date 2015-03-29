#!/usr/bin/python

infile = open('cit-HepPh.txt')

lines = infile.readlines()
dl={}
count = 0
for line in lines:
    v = line.split()
    if v[0] not in dl.keys():
        dl[v[0]] = []
        count += 1
        if count % 1000 == 0: 
            print "Read "+ str(count) + " nodes"
    dl[v[0]].append(v[1])
infile.close()

print "Finish reading"

outfile = open('citegraph', 'w')
o = str(len(dl)) + '\n'
outfile.write(o)
keys = dl.keys()
keys.sort()    
for key in keys:
    o = key + '\t' + str(len(dl[key]))
    for neighbor in dl[key]:
        o += '\t' + neighbor
    o += '\n'
    outfile.write(o)

outfile.close()
