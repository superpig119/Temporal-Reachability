#include "Feline.h"

bool operator <(nodeInfo &n1, nodeInfo &n2)
{
	vector<int>::iterator iv1, iv2;
	for(iv1 = n1.vCoor.begin(), iv2 = n2.vCoor.begin(); iv1 != n1.vCoor.end(); iv1++, iv2++)
	{
		if(*iv1 >= *iv2)
			return false;
	}
	return true;
}

void Feline::coorCreate()
{
	coorMax = vNode.size();
	topologicalOrdering();
	yCoor();
//	testNode();
}

void Feline::yCoor()
{
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	int i;
	for(i = 0; i < vNode.size(); i++)
	{
		md[i] = 0;
	}

	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		for(imEdge = (*ivnode).mEdge.begin(); imEdge != (*ivnode).mEdge.end(); imEdge++)
		{
			md[vNode[(*imEdge).first].ID]++;
		}
	}

	map<int, int> roots;	//<x, sNum>
	map<int, int>::reverse_iterator iroots;	
	map<int, int>::iterator imd;
	for(imd = md.begin(); imd != md.end(); imd++)
	{
		if((*imd).second == 0)
			roots[vNode[(*imd).first].vCoor[0]] = vNode[(*imd).first].ID;
	}

	int y = 1;
	while(roots.size())
	{
		int u = (*(roots.rbegin())).second;
		iroots = roots.rbegin();
		roots.erase((*iroots).first);
		vNode[u].vCoor.push_back(y);
		y++;
		for(imEdge = vNode[u].mEdge.begin(); imEdge != vNode[u].mEdge.end(); imEdge++)
		{
			md[vNode[(*imEdge).first].ID]--;
			if(md[vNode[(*imEdge).first].ID] == 0)
			{
				roots[vNode[(*imEdge).first].vCoor[0]] = vNode[(*imEdge).first].ID;
			}
		}
	}
}

void Feline::topologicalOrdering()
{
	int cnt = 0;
	int i;
	vector<int> TopoSort(vNode.size(), 0);
	DFSTravel(cnt, TopoSort);
	for(i = cnt - 1; i >= 0; i--)
	{
		vNode[TopoSort[i]].vCoor.push_back(cnt - i);
	}
}
	
void Feline::DFSTravel(int &cnt, vector<int> &TopoSort)
{
	int i, time;
	time = 0;
	vector<int> vParent(vNode.size(), -1);
	vector<bool> visited(vNode.size(), false);
	vector<int> vd(vNode.size(), 0);	//The time of the discovery
	vector<int> vf(vNode.size(), 0);	//The time of the finish

	for(i = 0; i < vNode.size(); i++)
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
	map<int, int>::iterator imEdge;
	nodeInfo n = vNode[sNum];
	for(imEdge = n.mEdge.begin(); imEdge != n.mEdge.end(); imEdge++)
	{
		if(!visited[vNode[(*imEdge).first].ID])
		{
			vParent[vNode[(*imEdge).first].ID] = sNum;
			DFS(vnode[(*imEdge).first].ID, visited, time, vd, vf, vParent, cnt, TopoSort);
		}
	}
	time++;
	vf[sNum] = time;
	TopoSort[cnt++] = sNum;
}


void Feline::findFP()
{
/*	vector<nodeInfo>::iterator ivnode;
	int i, j;
	nFP = 0;
	for(i = 0; i < vNode.size() - 1; i++)
	{
		for(j = i + 1; j < vNode.size(); j++)
		{
			cout << i << "\t" << j << endl;
			if(!Reachable(i, j) && vNode[i] < vNode[j])
			{
				vNode[i].vUnreachable.push_back(j);
				nFP++;
			}
		}
	}
	cout << nFP << " false positive totally!" << endl;*/
	Grid grid;
	grid.vNode = vNode;
	grid.buildGrid(coorMax);
//	grid.showGrid();
	grid.showGridInfo();
	vector<int> vr;
	vector<int>::iterator ivr;
	vr = grid.getNodes(2,2000,3,400);
	cout << ">>>" << vr.size() << endl;
//	for(ivr = vr.begin(); ivr != vr.end(); ivr++)
//		cout << *ivr << "\t" << vNode[*ivr].vCoor[0] << "\t" << vNode[*ivr].vCoor[1] << endl;; 
}

void Feline::findMaxCoor()
{
	vector<nodeInfo>::iterator ivnode;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{

	}
	
}

bool Feline::Reachable(int s1, int s2)
{
	if(s1 == s2)
		return true;
	if(vNode[s1] < vNode[s2])
	{
		map<int, int>::iterator imEdge;
		for(imEdge = vNode[s1].mEdge.begin(); imEdge != vNode[s1].mEdge.end(); imEdge++)
		{
			if(Reachable((*imEdge).first, s2))
				return true;
		}
	}
	return false;
}

void Feline::testNode()
{
	vector<nodeInfo>::iterator ivnode;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		cout << "ID:\t" << (*ivnode).ID << "\t" << (*ivnode).vCoor[0] << "\t" << (*ivnode).vCoor[1] << endl;
	}
}

void Feline::outputNodes()
{
	ofstream ofile("coordinate");
	vector<nodeInfo>::iterator ivnode;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		ofile << (*ivnode).ID << "\t" << (*ivnode).vCoor[0] << "\t" << (*ivnode).vCoor[1] << endl;
	}
	ofile.close();
}

void Feline::outputEdges()
{
	ofstream ofile("edges");
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		for(imEdge = (*ivnode).mEdge.begin(); imEdge != (*ivnode).mEdge.end(); imEdge++)
		{
			ofile << (*ivnode).ID << "\t" << (*imEdge).first << endl;
		}
	}
	ofile.close();
}
