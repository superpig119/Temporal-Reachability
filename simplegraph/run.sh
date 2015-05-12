#! /bin/bash

echo 0 > Recur

file=(ACC tquery tindex FPrate onR)
for ((i=0;i<${#file[@]};i++)) do
if [ -f "$file[i]" ]; then
rm $file[i]
fi
done

p=../data/simpleGraph/er/10000/0.1
#p=../data/simpleGraph/bi
d=(2 3 4 5 6 10 20 50 100 200)
#d=(2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)
#d=(50)

#for ((i=0;i<${#d[@]};i++)) do
for ((i=2;i<300;i++)) do
#    echo i${d[i]}
    ./onlineSearch $i
    mv coordinate i$i
	while read LINE
	do
		if [$LINE=="1"]; then
		break
		fi
	done < Recur
done

mv ACC $p
mv tquery $p
mv tindex $p
mv FPrate $p
mv onR $p
