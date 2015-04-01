#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <set>
#include <algorithm>
#include "nodeInfo.h"

using namespace std;

class SimpleGraph
{
public:
	int buildGraph();
	bool findSCC();	//False:no SCC	True:has SCC
	void tarjan(int i, vector<int> &vDFN, int &dIndex, int &Stop, vector<int> &vLOW, vector<bool> &vInstack, stack<nodeInfo> &sNode, int &Bcnt, vector<int> &vBelong);//Tarjan 
	void condense();
	void reachBFS();
    void BFS(int i, map<int, bool> &mVisited, vector<vector<int> > &vvNeighbor, int &count);

	void testSCC();
	void testGraph(vector<nodeInfo> &vNode);
	
	bool hasSCC;
	vector<nodeInfo> vnode;	//original graph
	vector<nodeInfo> vNode;	//condensed graph
    map<int, set<int> > msSCC;
	map<int, int> mOtoN;
};
