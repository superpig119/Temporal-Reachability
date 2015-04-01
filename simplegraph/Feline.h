#include "SimpleGraph.h"
#include "Grid.h"
#include <cstdlib>
#include <ctime>

class Feline : public SimpleGraph
{
public:
	void coorCreate();
	void topologicalOrdering();
	void yCoor();
	void DFSTravel(int &cnt, vector<int> &TopoSort);
	void DFS(int sNum, vector<bool> &visited, int &time, vector<int> &vd, vector<int> &vf, vector<int> &vParent, int &cnt, vector<int> &TopoSort);
	void highDCoor();
	bool Reachable(int s1, int s2, int &level);
	
	void findMaxCoor();
    void postRoot(int i, map<int, bool> &mVisited);
	void findFP();

	void testNode();
    void showEdges();	
	void outputEdges();	//output edge file
	void outputNodes();	//output coordiante file

    void randomTest();

	map<int, int> mdStatic;	//in-neighbor number
	int nFP;			//false positive number
	int d;
	map<int, set<int> > msFP;
	int coorMax;
    map<int, int> mTopo;//Topo order

//	map<int, set<int> > mheads;//out-neighbors
};

bool operator <(nodeInfo &n1, nodeInfo &n2);
bool coorCompare(nodeInfo n1, nodeInfo n2);
