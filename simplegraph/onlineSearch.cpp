#include "Feline.h"

int main()
{
	ifstream infile("filename");
	string filename;
	infile >> filename;

	Feline f;
	if(f.buildGraph(filename.c_str()) != -1)
    {
	    f.hasSCC = f.findSCC();
	//	sg.testGraph(sg.vnode);
//	    f.testSCC();
	    f.condense();
/*		if(f.hasSCC)
		    f.testGraph(f.vNode);
		else
			f.testGraph(f.vnode);*/
    }
	f.coorCreate();
	f.outputNodes();
	f.outputEdges();
	f.findFP();
	return 0;
}
