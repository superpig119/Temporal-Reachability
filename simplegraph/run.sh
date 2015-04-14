#! /bin/bash

p=../data/simpleGraph/smallworld/10000/20/0.3/
d=(2 3 4 5 6 10 20 50 100 200)

for ((i=0;i<${#d[@]};i++)) do
#    echo ${d[i]}
    ./onlineSearch ${d[i]}
    mv coordinate i${d[i]}
done

mv ACC $p
mv tquery $p
mv tindex $p
mv FPrate $p
mv onR $p
