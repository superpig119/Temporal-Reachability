#include "SimpleGraph.h"

int main()
{
	ifstream infile("filename");
	string filename;
	infile >> filename;

	SimpleGraph sg;
	sg.buildGraph(filename.c_str());
	sg.hasSCC = sg.findSCC();
	sg.testSCC();
	sg.condense();
	sg.testGraph();

	return 0;
}
