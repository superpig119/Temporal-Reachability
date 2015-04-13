#include "Feline.h"

int main()
{
	Feline f;
	if(f.buildGraph() != -1)
    {
//	    f.hasSCC = f.findSCC();
//		f.testGraph(f.vNode);
//		f.testGraph(f.vnode);
//	    f.testSCC();
//	    f.condense();
/*		if(f.hasSCC)
		    f.testGraph(f.vNode);
		else
			f.testGraph(f.vnode);*/
        clock_t t1, t2;
        t1 = clock();
	    f.coorCreate();
        t2 = clock();
        double duration = (double)(t2 - t1);
        cout << "Index Construction time:" << duration / CLOCKS_PER_SEC << endl;
	    f.outputNodes();
	    f.outputEdges();
        f.randomTest();
    }
	return 0;
}
