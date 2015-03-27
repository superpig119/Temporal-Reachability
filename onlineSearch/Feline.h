#include "TransformedGraph.h"

class Feline : public TGraph
{
public:
	void coorCreate();
	void topologicalOrdering();
	void yCoor();
	void DFSTravel(int &cnt, vector<int> &TopoSort);
	void DFS(int sNum, vector<bool> &visited, int &time, vector<int> &vd, vector<int> &vf, vector<int> &vParent, int &cnt, vector<int> &TopoSort);
	bool Reachable(int s1, int s2);
	void findFP();
	bool isNE(int s1, int s2);
	void findSkyline();
	bool isDome(int sNum);

	void testNode();
    void showEdges();
	void outputEdges();
	void outputNodes();

	map<int, int> md;	//in-neighbor number

//	map<int, set<int> > mheads;//out-neighbors
};
