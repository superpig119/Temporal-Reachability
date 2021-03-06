#include "Feline.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
	Feline f;
    stringstream ss;
    ss << argv[1];
    ss >> f.d;
    cout << f.d << endl;
	
	ofstream oRecur("Recur");
	oRecur << 0;
	oRecur.close();
//	f.findOptD();

	system("rm ACC");
	system("rm FPrate");
	system("rm onR");
	system("rm FPpercent");
	system("rm tquery");

	if(f.buildGraph() != -1)
    {
//	    f.hasSCC = f.findSCC();
//		f.testGraph(f.vNode);
//		f.testGraph(f.vnode);
//	    f.testSCC();
//	    f.condense();
//      f.testParent();
//		f.testGraph(f.vNode);
/*		if(f.hasSCC)
		    f.testGraph(f.vNode);
		else
			f.testGraph(f.vnode);*/
        clock_t t1, t2;
        t1 = clock();
	    f.coorCreate();
//		f.testNode();
        t2 = clock();
        double duration = (double)(t2 - t1);
        cout << "Index Construction time:" << duration / CLOCKS_PER_SEC << endl;
      
        ofstream ftindex("tindex", ofstream::app);
        ftindex << argv[1] << "\t" << duration / CLOCKS_PER_SEC << endl;
        ftindex.close();
/*		map<int, int> mFPNumber;
		f.Sample(mFPNumber);
		f.FPRemoveFromParent(mFPNumber);
		mFPNumber.clear();
		f.Sample(mFPNumber);
		f.FPRemoveFromParent(mFPNumber);
		mFPNumber.clear();
		f.Sample(mFPNumber);
		f.FPRemoveFromParent(mFPNumber);
		mFPNumber.clear();
		f.Sample(mFPNumber);
		f.FPRemoveFromParent(mFPNumber);
		mFPNumber.clear();
		f.Sample(mFPNumber);*/
	    f.outputNodes();
	    f.outputEdges();
//		f.testReachable();
//        f.randomTest();
    }
	return 0;
}
