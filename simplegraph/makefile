CXX=g++

onlineSearch:SimpleGraph.o 
	g++ -o onlineSearch onlineSearch.cpp SimpleGraph.o
	mv *.o ./obj
	mv *.gch ./obj

SimpleGraph.o:SimpleGraph.cpp
	$(CXX) -c SimpleGraph.cpp SimpleGraph.h

clean:
	rm onlineSearch
