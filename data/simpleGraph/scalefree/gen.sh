#!/bin/bash

d=(0.5 1 2 3)
size=10000

for ((i=0;i<${#d[@]};i++)) do
	echo ${d[i]}
	./n.py $size ${d[i]} $RANDOM
	./transnet.py bag
	rm bag
	mv databag $size/${d[i]}/
done

