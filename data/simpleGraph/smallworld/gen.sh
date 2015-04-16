#!/bin/bash

d=( 0.7 0.9 1)
size=100000
edge=20

for ((i=0;i<${#d[@]};i++)) do
	echo ${d[i]}
	./n.py $size $edge ${d[i]}
	./transnet.py wssmall
	rm wssmall
	rm tmp
	mv datawssmall $size/$edge/${d[i]}/
done

