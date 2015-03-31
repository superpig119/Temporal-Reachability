CXX=g++

onlineSearch:onlineSearch.o SimpleGraph.o Feline.o Grid.o
	g++ -o onlineSearch onlineSearch.cpp SimpleGraph.o Feline.o Grid.o
	mv *.o ./obj
	mv *.gch ./obj

SimpleGraph.o:SimpleGraph.cpp
	$(CXX) -c SimpleGraph.cpp SimpleGraph.h nodeInfo.h

Feline.o:Feline.cpp
	$(CXX) -c Feline.cpp Feline.h 

Grid.o:Grid.cpp
	$(CXX) -c Grid.cpp Grid.h nodeInfo.h

clean:
	rm onlineSearch
