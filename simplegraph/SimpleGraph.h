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
	list<int> lEdge;
	vector<int> vCoor;
	vector<int> vUnreachable;
}nodeInfo;

class SimpleGraph
{
public:
	void buildGraph(const char* fileName);
	void findSCC();
	void tarjan(int i, vector<int> &vDFN, int &dIndex, int &Stop, vector<int> &vLOW, vector<bool> &vInstack, stack<nodeInfo> &sNode, int &Bcnt, vector<int> &vBelong);//Tarjan 


	void testSCC();
	
	vector<nodeInfo> vnode;
    map<int, set<int> > msSCC;
};
