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
	int temporalID;	//node's temporal puppet
	int sNum;		//boost the efficiency for lookup
	int nodeType;	//0: inNode
					//1: outNode
	int x, y;
}nodeInfo;

typedef struct EDGEINFO
{
	int dsNum;	//destination node
	int sTime, eTime;
	int edgeType;	//0: edge from the original graph
					//1: edge within each node
					//2: edge between each node's in/out
}edgeInfo;

typedef struct NODE
{
	nodeInfo ni;
	list<edgeInfo> lEdge;
}node;

class TGraph
{
public:
	void buildGraph(const char* fileName);
	void countInOut(const char* fileName);
	void createNodes();
	void addEdges(const char* fileName);

    void findSCC();
    void tarjan(int i, vector<int> &vDFN, int &dIndex, int &stop, vector<int> &vLOW, vector<bool> &vInstack, stack<node> &sNode, int &Bcnt, vector<int> &vBelong);

	//	bool nodeTimeCompare(node n1, node n2);
	void testCountInOut();
	void testNodes();
	void testSCC();	
	
	vector<node> vnode;
	int nodeNum;
	map<int, map<int, bool> > mmInTime, mmOutTime;
	map<int, map<int, int> > mmInSnum, mmOutSnum;
    map<int, set<int> > msSCC;
};
