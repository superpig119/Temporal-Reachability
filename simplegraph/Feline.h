#include "SimpleGraph.h"
#include "Grid.h"

class Feline : public SimpleGraph
{
public:
	void coorCreate();
	void topologicalOrdering();
	void yCoor();
	void DFSTravel(int &cnt, vector<int> &TopoSort);
	void DFS(int sNum, vector<bool> &visited, int &time, vector<int> &vd, vector<int> &vf, vector<int> &vParent, int &cnt, vector<int> &TopoSort);
	bool Reachable(int s1, int s2);
	
	void findMaxCoor();
	void findFP();

	void testNode();
    void showEdges();	
	void outputEdges();	//output edge file
	void outputNodes();	//output coordiante file

	map<int, int> md;	//in-neighbor number
	int nFP;			//false positive number
	map<int, set<int> > msFP;
	int coorMax;

//	map<int, set<int> > mheads;//out-neighbors
};

bool operator <(nodeInfo &n1, nodeInfo &n2);
