#include "Feline.h"

int main(int argc, char* argv[])
{
    stringstream ss;
	Feline f;
    ss << argv[1];
    ss >> f.d;
    cout << f.d << endl;
	if(f.buildGraph() != -1)
    {
//	    f.hasSCC = f.findSCC();
//		f.testGraph(f.vNode);
//		f.testGraph(f.vnode);
//	    f.testSCC();
//	    f.condense();
//		f.testGraph(f.vNode);
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
      
        ofstream ftindex("tindex", ofstream::app);
        ftindex << argv[1] << "\t" << duration / CLOCKS_PER_SEC << endl;
        ftindex.close();

	    f.outputNodes();
	    f.outputEdges();

		f.testReachable();
//        f.randomTest();
    }
	return 0;
}
