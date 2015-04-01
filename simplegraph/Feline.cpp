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
	
bool coorCompare(nodeInfo n1, nodeInfo n2)
{
	if(n1 < n2)
		return true;
	else
	{
		vector<int>::iterator iv1, iv2;
		int t1 = 0;
		int	t2 = 0;
		for(iv1 = n1.vCoor.begin(); iv1 != n1.vCoor.end(); iv1++)
			t1 += (*iv1);
		for(iv2 = n2.vCoor.begin(); iv2 != n2.vCoor.end(); iv2++)
			t2 += (*iv2);
		if(t1 < t2)
			return true;
		else
			return false;
	}
}

void Feline::coorCreate()
{
	coorMax = vNode.size();
	topologicalOrdering();
	yCoor();
	highDCoor();
//	testNode();
}

void Feline::yCoor()
{
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	int i;
	for(i = 0; i < vNode.size(); i++)
	{
		mdStatic[i] = 0;
	}

	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		for(imEdge = (*ivnode).mEdge.begin(); imEdge != (*ivnode).mEdge.end(); imEdge++)
		{
			mdStatic[vNode[(*imEdge).first].ID]++;
		}
	}

	map<int, int> md(mdStatic);
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
        mTopo[cnt - i] = TopoSort[i];
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

void Feline::highDCoor()
{
	Conf cf;
	cf.readConf();
	d = cf.dimension;

	int r = d - 2;
	int i, j;
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	for(i = 0; i < r; i++)
	{
		map<int, int> md(mdStatic);//copy of mdStatic
//		map<int, int> roots;	//<x, sNum>
//		vector<nodeInfo> roots;
//		vector<nodeInfo>::iterator iroots;	
        map<vector<int>, int> mroots;   //coor,ID
        map<vector<int>, int>::iterator imroots;   //coor,ID
        map<vector<int>, int>::reverse_iterator rimroots;   //coor,ID
		map<int, int>::iterator imd;
		for(imd = md.begin(); imd != md.end(); imd++)
		{
			if((*imd).second == 0)
			{
//				roots.push_back(vNode[(*imd).first]);
                mroots[vNode[(*imd).first].vCoor] = (*imd).first;
			}
		}
//		sort(roots.begin(), roots.end(), coorCompare);
	
		int c = 1;
		while(mroots.size())
		{
            int u = (*(mroots.rbegin())).second;
            rimroots = mroots.rbegin();
            mroots.erase((*rimroots).first);
            vNode[u].vCoor.push_back(c);
//			nodeInfo u = *(roots.end() - 1);
//			iroots = roots.end() - 1;
//			roots.erase(iroots);
//			vNode[u.ID].vCoor.push_back(c);
			c++;
			for(imEdge = vNode[u].mEdge.begin(); imEdge != vNode[u].mEdge.end(); imEdge++)
			{
				md[vNode[(*imEdge).first].ID]--;
				if(md[vNode[(*imEdge).first].ID] == 0)
				{
				//	roots.push_back(vNode[(*imEdge).first]);
                    mroots[vNode[(*imEdge).first].vCoor] = vNode[(*imEdge).first].ID;
				}
			}
//			sort(roots.begin(), roots.end(), coorCompare);
		}
	}
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
    findMaxCoor();
    vector<nodeInfo>::iterator ivnode;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		cout << (*ivnode).ID << "\t" << (*ivnode).vMaxCoor[0] << "\t" << (*ivnode).vMaxCoor[1] << endl;
	}
    
}

void Feline::findMaxCoor()
{
    map<int, bool> mVisited;
	vector<nodeInfo>::iterator ivnode;
    int d = (*(vNode.begin())).vCoor.size();
    int i;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
        for(i = 0; i < d; i++)
        {
            (*ivnode).vMaxCoor.push_back(0);
        }
        mVisited[(*ivnode).ID] = false;
	}
    
    for(i = 0; i < vNode.size(); i++)
    {
        if(!mVisited[mTopo[i]])
        {
            postRoot(i, mVisited);
        }
    }
	
}

void Feline::postRoot(int i, map<int, bool> &mVisited)
{
    map<int, int>::iterator imEdge;
    int j;
    if(vNode[i].mEdge.size() != 0)
    {
        for(imEdge = vNode[i].mEdge.begin(); imEdge != vNode[i].mEdge.end(); imEdge++)
        {
            if(!mVisited[(*imEdge).first])
                postRoot((*imEdge).first, mVisited);
        }
        mVisited[i] = true;
        for(imEdge = vNode[i].mEdge.begin(); imEdge != vNode[i].mEdge.end(); imEdge++)
        {
            for(j = 0; j < vNode[0].vMaxCoor.size(); j++)
            {
                if(vNode[(*imEdge).first].vMaxCoor[j] > vNode[i].vMaxCoor[j])
                {
                    vNode[i].vMaxCoor[j] = vNode[(*imEdge).first].vMaxCoor[j];
                }
            }
        }
    }
    else
    {
        int k;
        for(k = 0; k < vNode[i].vCoor.size(); k++)
        {
            vNode[i].vMaxCoor[k] = vNode[i].vCoor[k];
        }
        mVisited[i] = true;
    }
}

bool Feline::Reachable(int s1, int s2, int &level)
{
    level++;
	if(s1 == s2)
		return true;
	if(vNode[s1] < vNode[s2])
	{
		map<int, int>::iterator imEdge;
		for(imEdge = vNode[s1].mEdge.begin(); imEdge != vNode[s1].mEdge.end(); imEdge++)
		{
			if(Reachable((*imEdge).first, s2, level))
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
	vector<int>::iterator ivc;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		ofile << (*ivnode).ID;
		for(ivc = (*ivnode).vCoor.begin(); ivc != (*ivnode).vCoor.end(); ivc++)
		{
			ofile << "\t" << *ivc;
		}
		ofile << endl;
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
    
void Feline::randomTest()
{   
    int n = vNode.size();
    int n1, n2, i;
    int level;
    float mis = 0;
    for(i = 0; i < n/2; i++)
    {
        level = 0;
        srand(i);
        n1 = rand() % n;
        n2 = rand() % n;
//       cout << n1 << "\t" << n2 << endl;
        Reachable(n1, n2, level);
        if(level > 1)
            mis++;
    }
    float rate = mis/(n/2);
    cout << "d:" << d << "\ttotal test:" << n/2 << "\tMiss:" << mis << "\tRate:" <<  rate << endl;
}
