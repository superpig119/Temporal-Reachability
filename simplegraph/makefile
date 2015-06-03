CXX=g++

onlineSearch:onlineSearch.o SimpleGraph.o Feline.o Grid.o Conf.o
	g++ -g -o onlineSearch onlineSearch.cpp SimpleGraph.o Feline.o Grid.o Conf.o 
	mv *.o ./obj

SimpleGraph.o:SimpleGraph.cpp
	$(CXX) -g -c SimpleGraph.cpp 

Feline.o:Feline.cpp
	$(CXX) -g -c Feline.cpp 

Grid.o:Grid.cpp
	$(CXX) -g -c Grid.cpp 

Conf.o:Conf.cpp
	$(CXX) -g -c Conf.cpp

clean:
	rm onlineSearch
