CXX=g++

onlineSearch:onlineSearch.o TransformedGraph.o Feline.o
	g++ -o onlineSearch onlineSearch.cpp TransformedGraph.o Feline.o
	mv *.o ./obj
	mv *.gch ./obj


TransformedGraph.o:TransformedGraph.cpp
	$(CXX) -c TransformedGraph.cpp TransformedGraph.h

Feline.o:Feline.cpp
	$(CXX) -c Feline.cpp Feline.h

clean:
	rm onlineSearch
