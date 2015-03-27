#include "Feline.h"

void Feline::coorCreate()
{
	topologicalOrdering();
	yCoor();
	testNode();
}

bool Feline::Reachable(int s1, int s2)
{
	if(s1 == s2)
		return true;
	if(isNE(s1, s2))
	{
		list<edgeInfo>::iterator ilEdge;
		for(ilEdge = vnode[s1].lEdge.begin(); ilEdge != vnode[s1].lEdge.end(); ilEdge++)
		{
			if(Reachable((*ilEdge).dsNum, s2))
				return true;
		}
	}
	return false;
}

bool Feline::isNE(int s1, int s2)
{
	if(vnode[s1].ni.x <= vnode[s2].ni.x && vnode[s1].ni.y <= vnode[s2].ni.y)
		return true;
	else
		return false;
}

void Feline::yCoor()
{
	vector<node>::iterator ivnode;
	list<edgeInfo>::iterator ilEdge;
	int i;
	for(i = 0; i < vnode.size(); i++)
	{
		md[i] = 0;
	}

	for(ivnode = vnode.begin(); ivnode != vnode.end(); ivnode++)
	{
		for(ilEdge = (*ivnode).lEdge.begin(); ilEdge != (*ivnode).lEdge.end(); ilEdge++)
		{
			md[vnode[(*ilEdge).dsNum].ni.sNum]++;
		}
	}

	map<int, int> roots;	//<x, sNum>
	map<int, int>::reverse_iterator iroots;	
	map<int, int>::iterator imd;
	for(imd = md.begin(); imd != md.end(); imd++)
	{
		if((*imd).second == 0)
			roots[vnode[(*imd).first].ni.x] = vnode[(*imd).first].ni.sNum;
	}

//	int y = vnode.size();
	int y = 1;
	while(roots.size())
	{
		int u = (*(roots.rbegin())).second;
		iroots = roots.rbegin();
		roots.erase((*iroots).first);
		vnode[u].ni.y = y;
		y++;
		for(ilEdge = vnode[u].lEdge.begin(); ilEdge != vnode[u].lEdge.end(); ilEdge++)
		{
			md[vnode[(*ilEdge).dsNum].ni.sNum]--;
			if(md[vnode[(*ilEdge).dsNum].ni.sNum] == 0)
			{
				roots[vnode[(*ilEdge).dsNum].ni.x] = vnode[(*ilEdge).dsNum].ni.sNum;
			}
		}
	}
}

void Feline::topologicalOrdering()
{
	int cnt = 0;
	int i;
	vector<int> TopoSort(vnode.size(), 0);
	DFSTravel(cnt, TopoSort);
	for(i = cnt - 1; i >= 0; i--)
	{
//		cout << i << "\t" << vnode[TopoSort[i]].ni.ID << "\t" << vnode[TopoSort[i]].ni.temporalID   << endl ;
		vnode[TopoSort[i]].ni.x = cnt - i;
//		cout << cnt - i << endl;
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
		if(!visited[vnode[(*ilEdge).dsNum].ni.sNum])
		{
			vParent[vnode[(*ilEdge).dsNum].ni.sNum] = sNum;
			DFS(vnode[(*ilEdge).dsNum].ni.sNum, visited, time, vd, vf, vParent, cnt, TopoSort);
		}
	}
	time++;
	vf[sNum] = time;
	TopoSort[cnt++] = sNum;
}

void Feline::findSkyline()
{
	vector<bool> vDomed(vnode.size(), false);
	vector<bool> vVisited(vnode.size(), true);
	int i = vnode.size();
	while(i)
	{
		
	}
}

void Feline::findFP()
{
}

void Feline::testNode()
{
	cout << "ID\ttemporalID\tsNUm\ttype\tx\ty" << endl;
	vector<node>::iterator ivnode;
	for(ivnode = vnode.begin(); ivnode != vnode.end(); ivnode++)
	{
		cout << "ID:\t" << (*ivnode).ni.ID << "\t" << (*ivnode).ni.temporalID << "\t" << (*ivnode).ni.sNum << "\t" << (*ivnode).ni.nodeType << "\t" << (*ivnode).ni.x << "\t" << (*ivnode).ni.y << endl;
	}
}

void Feline::showEdges()
{
	vector<node>::iterator ivnode;
	list<edgeInfo>::iterator ilEdge;
	for(ivnode = vnode.begin(); ivnode != vnode.end(); ivnode++)
	{
		for(ilEdge = (*ivnode).lEdge.begin(); ilEdge != (*ivnode).lEdge.end(); ilEdge++)
		{
			cout << (*ivnode).ni.sNum << "\t" << (*ilEdge).dsNum << "\t" << (*ilEdge).edgeType << endl;
		}
	}
}

void Feline::outputNodes()
{
	ofstream ofile("coordinate");
	vector<node>::iterator ivnode;
	for(ivnode = vnode.begin(); ivnode != vnode.end(); ivnode++)
	{
		ofile << "ID:\t" << (*ivnode).ni.ID << "\t" << (*ivnode).ni.temporalID << "\t" << (*ivnode).ni.sNum << "\t" << (*ivnode).ni.nodeType << "\t" << (*ivnode).ni.x << "\t" << (*ivnode).ni.y << endl;
	}
	ofile.close();
}

void Feline::outputEdges()
{
	ofstream ofile("edges");
	vector<node>::iterator ivnode;
	list<edgeInfo>::iterator ilEdge;
	for(ivnode = vnode.begin(); ivnode != vnode.end(); ivnode++)
	{
		for(ilEdge = (*ivnode).lEdge.begin(); ilEdge != (*ivnode).lEdge.end(); ilEdge++)
		{
			ofile << (*ivnode).ni.sNum << "\t" << (*ilEdge).dsNum << "\t" << (*ilEdge).edgeType << endl;
		}
	}
	ofile.close();
}
