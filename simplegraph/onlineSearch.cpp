#include "SimpleGraph.h"

int main()
{
	ifstream infile("filename");
	string filename;
	infile >> filename;

	SimpleGraph sg;
	sg.buildGraph(filename.c_str());
	sg.findSCC();
	sg.testSCC();

	return 0;
}
