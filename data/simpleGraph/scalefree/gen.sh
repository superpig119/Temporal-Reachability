#!/bin/bash

d=(10 20 30 50 100)
size=10000

for ((i=0;i<${#d[@]};i++)) do
	echo ${d[i]}
	./n.py $size ${d[i]} $RANDOM
	./transnet.py bag
	rm bag
	mv databag $size/${d[i]}/
done

