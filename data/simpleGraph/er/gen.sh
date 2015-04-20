#!/bin/bash

d=(0.05 0.1 0.15 0.2 0.25 0.3 0.5 0.7 0.9 1)
size=10000

for ((i=0;i<${#d[@]};i++)) do
	echo ${d[i]}
	./n.py $size ${d[i]} $RANDOM
	./transnet.py erg
	rm erg
	mv dataerg $size/${d[i]}/
done

