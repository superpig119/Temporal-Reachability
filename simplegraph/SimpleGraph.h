#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

typedef struct NODEINFO
{
	int ID;			//node's orginal ID
	map<int, int> mEdge;
	vector<int> vCoor;
	vector<int> vUnreachable;
}nodeInfo;

class SimpleGraph
{
public:
	void buildGraph(const char* fileName);
	bool findSCC();	//False:no SCC	True:has SCC
	void tarjan(int i, vector<int> &vDFN, int &dIndex, int &Stop, vector<int> &vLOW, vector<bool> &vInstack, stack<nodeInfo> &sNode, int &Bcnt, vector<int> &vBelong);//Tarjan 
	void condense();
	

	void testSCC();
	void testGraph();
	
	bool hasSCC;
	vector<nodeInfo> vnode;	//original graph
	vector<nodeInfo> vNode;	//condensed graph
    map<int, set<int> > msSCC;
	map<int, int> mOtoN;
};
