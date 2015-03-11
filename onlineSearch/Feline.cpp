#include "Feline.h"

void Feline::coorCreate()
{
	topologicalOrdering();
}
	
void Feline::topologicalOrdering()
{
	int cnt = 0;
	int i;
	vector<int> TopoSort(vnode.size(), 0);
	DFSTravel(cnt, TopoSort);
	for(i = cnt - 1; i >=0; i--)
	{
		cout << vnode[TopoSort[i]].ni.ID << "\t" << vnode[TopoSort[i]].ni.temporalID   << endl ;
	}
	cout << endl;
}
	
void Feline::DFSTravel(int &cnt, vector<int> &TopoSort)
{
	int i, time;
	time = 0;
	vector<int> vParent(vnode.size(), -1);
	vector<bool> visited(vnode.size(), false);
	vector<int> vd(vnode.size(), 0);	//The time of the discovery
	vector<int> vf(vnode.size(), 0);	//The time of the finish

	for(i = 0; i < vnode.size(); i++)
	{
		if(!visited[i])
			DFS(i, visited, time, vd, vf, vParent, cnt, TopoSort);
	}
}
	
void Feline::DFS(int sNum, vector<bool> &visited, int &time, vector<int> &vd, vector<int> &vf, vector<int> &vParent, int &cnt, vector<int> &TopoSort)
{
	visited[sNum] = true;
	time++;
	vd[sNum] = time;
	list<edgeInfo>::iterator ilEdge;
	node n = vnode[sNum];
	for(ilEdge = n.lEdge.begin(); ilEdge != n.lEdge.end(); ilEdge++)
	{
		if(!visited[(*ilEdge).dNode.sNum])
		{
			vParent[(*ilEdge).dNode.sNum] = sNum;
			DFS((*ilEdge).dNode.sNum, visited, time, vd, vf, vParent, cnt, TopoSort);
		}
	}
	time++;
	vf[sNum] = time;
	TopoSort[cnt++] = sNum;
}
