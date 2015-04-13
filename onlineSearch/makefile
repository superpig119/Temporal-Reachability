CXX=g++

onlineSearch:onlineSearch.o SimpleGraph.o Feline.o Grid.o Conf.o
    g++ -o onlineSearch onlineSearch.cpp SimpleGraph.o Feline.o Grid.o Conf.o
    mv *.o ./obj
#   mv *.gch ./obj

SimpleGraph.o:SimpleGraph.cpp
$(CXX) -c SimpleGraph.cpp 

Feline.o:Feline.cpp
    $(CXX) -c Feline.cpp 

Grid.o:Grid.cpp
    $(CXX) -c Grid.cpp 

Conf.o:Conf.cpp
    $(CXX) -c Conf.cpp

clean:
rm onlineSearch
