#include "TransformedGraph.h"

class Feline : public TGraph
{
public:
	void coorCreate();
	void topologicalOrdering();
	void DFSTravel(int &cnt, vector<int> &TopoSort);
	void DFS(int sNum, vector<bool> &visited, int &time, vector<int> &vd, vector<int> &vf, vector<int> &vParent, int &cnt, vector<int> &TopoSort);
};
