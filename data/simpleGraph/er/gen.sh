#/bin/bash

d=(0.00001 0.00005 0.0001 0.0005 0.001)
size=10000

for ((i=0;i<${#d[@]};i++)) do
	echo ${d[i]}
	./n.py $size ${d[i]} $RANDOM
	./transnet.py erg
	rm erg
	mv dataerg $size/${d[i]}/
done

