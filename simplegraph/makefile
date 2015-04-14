CXX=g++-4.7

onlineSearch:onlineSearch.o SimpleGraph.o Feline.o Grid.o Conf.o
	g++-4.7 -o onlineSearch onlineSearch.cpp SimpleGraph.o Feline.o Grid.o Conf.o -std=c++11
	mv *.o ./obj
#	mv *.gch ./obj

SimpleGraph.o:SimpleGraph.cpp
	$(CXX) -c SimpleGraph.cpp 

Feline.o:Feline.cpp
	$(CXX) -c Feline.cpp -std=c++11

Grid.o:Grid.cpp
	$(CXX) -c Grid.cpp 

Conf.o:Conf.cpp
	$(CXX) -c Conf.cpp

clean:
	rm onlineSearch
