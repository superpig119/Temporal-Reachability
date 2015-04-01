#include "Feline.h"

int main()
{
	Feline f;
	if(f.buildGraph() != -1)
    {
	    f.hasSCC = f.findSCC();
//		f.testGraph(f.vNode);
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
    f.randomTest();
//    f.reachBFS();
//	f.findFP();
	return 0;
}
