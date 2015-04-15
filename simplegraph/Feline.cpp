#include "Feline.h"

bool operator <(nodeInfo &n1, nodeInfo &n2)
{
	vector<int>::iterator iv1, iv2;
	for(iv1 = n1.vCoor.begin(), iv2 = n2.vCoor.begin(); iv1 != n1.vCoor.end() && iv2 != n2.vCoor.end(); iv1++, iv2++)
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
//	d = cf.dimension;

	int r = d - 2;
	int i, j;
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	for(i = 0; i < r; i++)
	{
		map<int, int> md(mdStatic);//copy of mdStatic
        map<vector<int>, int, vCompare> mroots;   //coor,ID
        map<vector<int>, int, vCompare>::iterator imroots;   //coor,ID
        map<vector<int>, int, vCompare>::reverse_iterator rimroots;   //coor,ID
		map<int, int>::iterator imd;
        vector<int>::iterator ivi;
        vector<int>::const_iterator icvi;
		for(imd = md.begin(); imd != md.end(); imd++)
		{
			if((*imd).second == 0)
			{
                mroots[vNode[(*imd).first].vCoor] = (*imd).first;
			}
		}
		int c = 1;
		
		while(mroots.size())
		{
            int u = (*(mroots.rbegin())).second;
            rimroots = mroots.rbegin();
            mroots.erase((++rimroots).base());
            vNode[u].vCoor.push_back(c);
			c++;
			for(imEdge = vNode[u].mEdge.begin(); imEdge != vNode[u].mEdge.end(); imEdge++)
			{
				md[vNode[(*imEdge).first].ID]--;
				if(md[vNode[(*imEdge).first].ID] == 0)
				{
                    mroots.insert(pair<vector<int>, int>(vNode[(*imEdge).first].vCoor,vNode[(*imEdge).first].ID));
				}
			}
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
	if(noRecur == 0)	//need online search
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
	else
	{
		if(vNode[s1] < vNode[s2])
			return true;
		else
			return false;
	}
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
    int level = 0;
    float mis = 0;
    float online = 0;
    clock_t t1, t2;
    t1 = clock();
    cout << "Reachable Test:" << endl;
    
	ifstream ifn("noRecur");
	ifn >> noRecur;
	ifn.close();

	for(i = 0; i < n; i++)
    {
        level = 0;
        srand(i);
        n1 = rand() % n;
        n2 = rand() % n;
        int m1 = n1;
        int m2 = n2;
  /*      if(hasSCC)
        {
            m1 = mOtoN[n1];
            m2 = mOtoN[n2];
        }
    */   
        bool b = Reachable(m1, m2, level);
        //level>1 means it has to search online and m1 < m2
        //!b means it is not reachable
        //so it is False Positive Ratio
        if(level > 1 && !b) 
        {
            mis++;
 //           cout << "Cannot reach:" << m1 << "\t" << m2 << endl;
        }
        //online search ratio
        if(level > 1)
        {
            online++;
        }
    }
    t2 = clock();
    float FPrate = mis/online;
    float Accurate = 1 - mis/(n);
    float onlineRate = online / n;
    cout << "d:" << d << "\ttotal test:" << n/2 << "\tMiss:" << mis << "\tFPRate:" <<  FPrate << "\tAcc Rate:" << Accurate << "\tOnline Rate:" << onlineRate << endl;
    double duration = (double)(t2 - t1);
    cout << "Average query time:" << duration / n / CLOCKS_PER_SEC << endl;

    ofstream fACC("ACC", ofstream::app);
    fACC << d << "\t" << Accurate << endl;
    fACC.close();

    ofstream fFPrate("FPrate", ofstream::app);
    fFPrate << d << "\t" << FPrate << endl;
    fFPrate.close();

    ofstream fonR("onR", ofstream::app);
    fonR << d << "\t" << onlineRate << endl;
    fonR.close();

    ofstream ftquery("tquery", ofstream::app);
    ftquery << d << "\t" << duration / n /CLOCKS_PER_SEC << endl;
    ftquery.close();
	
		
	ofstream fn("noRecur");
	{
		if(Accurate == 1)
			fn << 1;
		else
			fn << 0;
	}
	fn.close();
}
