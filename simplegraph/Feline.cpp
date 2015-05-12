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

	int j;
	for(j = 0; j < vNode.size(); j++)
		dp.push_back(0);
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		dp[(*ivnode).ID] = (*ivnode).vCoor[1];
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
	//	cout << (*imEdge).first << endl;
		if(!visited[vNode[(*imEdge).first].ID])
		{
			vParent[vNode[(*imEdge).first].ID] = sNum;
			DFS(vNode[(*imEdge).first].ID, visited, time, vd, vf, vParent, cnt, TopoSort);
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
	genTestSet();

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

		cout << endl << i + 2<< endl;
		randomTest();
		if(noRecur == 1)
			break;
//This piece of code is to compare the k-1 and k coordinate
//After initialization then call testD
/*		int j;
		if(i != 0)
		{
			for(j = 0; j < dp.size(); j++)
				dp[j] = dq[j];
		}

		if(i == 0)
		{
			for(j = 0; j < vNode.size(); j++)
				dq.push_back(0);
			for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
			{
				dq[(*ivnode).ID] = (*ivnode).vCoor[i + 2];
			}
		}
		else
		{
			for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
			{
				dq[(*ivnode).ID] = (*ivnode).vCoor[i + 2];
			}
		}
		cout << endl << i+2 << " dimenstion" << endl;
		testD();*/
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

bool Feline::ReachableNoneRecur(int s1, int s2, int &level)
{
    if(noRecur == 0)
    {
        if(vNode[s1] < vNode[s2])
        {
            map<int, int> mvisited;
			map<int, int>::iterator imEdge;
            queue<int> q;
            q.push(s1);
            while(!q.empty())
            {
                level++;
                int nt = q.front();
                q.pop();
			    for(imEdge = vNode[nt].mEdge.begin(); imEdge != vNode[nt].mEdge.end(); imEdge++)
                {
                    if((*imEdge).first == s2)
                        return true;
                    else
                    {
                        if(mvisited.find((*imEdge).first) == mvisited.end() && vNode[(*imEdge).first] < vNode[s2])
                        {
                            q.push((*imEdge).first);
                            mvisited[(*imEdge).first] = 1;
                        }
                    }
                }
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

void Feline::findOptD()
{
	int i;
	noRecur = 1;
	for(i = 2; i < 300; i++)
	{
		d = i;
		if(noRecur)
		{
			if(buildGraph() != -1)
			{
				clock_t t1, t2;
				t1 = clock();
				coorCreate();
				t2 = clock();
				double duration = (double)(t2 - t1);
				cout << "Index Construction time:" << duration / CLOCKS_PER_SEC << endl;
      
				ofstream ftindex("tindex", ofstream::app);
				ftindex << d << "\t" << duration / CLOCKS_PER_SEC << endl;
				ftindex.close();

				outputNodes();
				outputEdges();
				randomTest();
			}
		}
		else
		{
			cout << i << " is the optimal dimension" << endl;
			break;
		}
	}
}

void Feline::genTestSet()
{
	int i, n1, n2;
	int ttest = vNode.size() *10;
	for(i = 0; i < ttest; i++)
	{
        n1 = rand() % vNode.size();
        n2 = rand() % vNode.size();
		pair<int, int> ptmp = make_pair(n1, n2);
		mRandom[ptmp] = 1;
	}
}

void Feline::randomTest()
{   
    int n = vNode.size();
//	int n = 4000;
    int n1, n2, i;
    int level = 0;
    float mis = 0;
    float online = 0;
    clock_t t1, t2;
    t1 = clock();
    cout << "Reachable Test:" << endl;
    
	ifstream ifn("Recur");
	ifn >> noRecur;
	ifn.close();

	int ttest = 10 * n;
    srand((unsigned)time(NULL));
	map<pair<int, int>, int >::iterator imR;
	ttest = mRandom.size();
	for(i = 0, imR = mRandom.begin(); i < ttest; i++, imR++)
    {
        level = 0;
//        n1 = rand() % vNode.size();
//        n2 = rand() % vNode.size();
        int m1 = (*imR).first.first;
        int m2 = (*imR).first.second;
  /*      if(hasSCC)
        {
            m1 = mOtoN[n1];
            m2 = mOtoN[n2];
        }
    */   
//		cout << m1 << "\t" << m2 << "\t:";
        bool b = ReachableNoneRecur(m1, m2, level);
/*		if(!b)
			cout << "cannot reach!" << endl;
		else
			cout << "can reach!" << endl;*/
//        bool b = Reachable(m1, m2, level);
        //level>1 means it has to search online and m1 < m2
        //!b means it is not reachable
        //so it is False Positive Ratio
        if(level >= 1 && !b) 
        {
            mis++;
//			cout << "FP!" << endl;
        }

        //online search ratio
        if(level >= 1)
        {
            online++;
        }
    }
    t2 = clock();
    float FPrate = mis/online;
    float Accurate = 1 - mis/(ttest);
    float onlineRate = online / ttest;
	if(noRecur == 1)
	{
		FPrate = 0;
		Accurate = 1;
		onlineRate = 0;
	}
	if(Accurate == 1)
	{
		onlineRate = 0;
		noRecur = 1;
		t1 = clock();
		for(i = 0; i < ttest; i++)
		{
			n1 = rand() % vNode.size();
			n2 = rand() % vNode.size();
			level = 0;
			bool b = Reachable(n1, n2, level);
		}
		t2 = clock();
	}

    cout << "d:" << d << "\ttotal test:" << ttest << "\tMiss:" << mis << "\tFPRate:" <<  FPrate << "\tAcc Rate:" << Accurate << "\tOnline Rate:" << onlineRate << endl;
    double duration = (double)(t2 - t1);
    cout << "Average query time:" << duration / ttest / CLOCKS_PER_SEC << endl;

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
	
		
	ofstream fn("Recur");
	{
		if(Accurate == 1)
			fn << 1;
		else
			fn << 0;
	}
	fn.close();
}
	
float Feline::EucliDistance(vector<int> &v1, vector<int> &v2)
{
	double dist = 0;
	double tmp = 0;
	vector<int>::iterator iv1, iv2;
	for(iv1 = v1.begin(), iv2 = v2.begin(); iv1 != v1.end(); iv1++, iv2++)
	{
		tmp += pow(*iv1 - *iv2, 2);
	}

	return (float)sqrt(tmp);
}


int Feline::EditDistance(vector<int> &v1, vector<int> &v2)
{
	vector<int> t;
	int i, j, upleft, tmp, up;
	for(i = 0; i <= v1.size(); i++)
		t.push_back(i);
	for(i = 0; i <= v1.size(); i++)
	{
		upleft = t[0];
		t[0] = i;
		for(j = 1; j <= v1.size(); j++)
		{
			up = t[1];
			if(v2[i-1] != v1[j-1])
			{
				tmp = t[j];
				t[j] = min(min(up, t[j-1]), upleft) + 1;
				upleft = tmp;
			}
			else
			{
				tmp = t[j];
				t[j] = upleft;
				upleft = tmp;
			}
		}
	}

	return t[v1.size()];
}

int Feline::LCS(vector<int> &v1, vector<int> &v2)
{
	vector<int> t;
	int i, j, upleft, tmp, up;
	for(i = 0; i <= v1.size(); i++)
		t.push_back(0);
	for(i = 0; i <= v1.size(); i++)
	{
		upleft = t[0];
		t[0] = 0;
		for(j = 1; j <= v1.size(); j++)
		{
			up = t[j];
			if(v2[i-1] == v1[j-1])
			{
				tmp = t[j];
				t[j] = upleft + 1;
				upleft = tmp;
			}
			else
			{
				tmp = t[j];
				t[j] = max(t[j-1], up);
				upleft = tmp;
			}
		}
	}
	
	vector<int>::iterator iv;
	int max = 0;
	for(iv = t.begin(); iv != t.end(); iv++)\
		if(*iv > max)
			max = *iv;

	return max;
}
	
int Feline::Diff(vector<int> &v1, vector<int> &v2)
{
	int dist = 0;
	vector<int>::iterator iv1, iv2;
	for(iv1 = v1.begin(), iv2 = v2.begin(); iv1 != v1.end(); iv1++, iv2++)
	{
		if(*iv1 != *iv2)
			dist++;
	}
	return dist++;
}

void Feline::testD()
{
	cout << "Euclid Dist:\t" << EucliDistance(dp, dq) << endl;
	cout << "Edit Dist:\t" << EditDistance(dp, dq) << endl;
	cout << "Diff Dist:\t" << Diff(dp, dq) << endl;
	cout << "LCS:\t" << LCS(dp, dq) << endl;
}

void Feline::testReachable()
{
	ifstream ifile("testPairs");
	int t1,t2;
	vector<int> v1,v2;
	vector<int>::iterator iv1, iv2;
	int level = 0;
	while(ifile >> t1)
	{
		v1.push_back(t1);
		ifile >> t2;
		v2.push_back(t2);
	}
	
	bool b;
	noRecur = 0;
	for(iv1 = v1.begin(), iv2 = v2.begin(); iv1 != v1.end(); iv1++, iv2++)
	{
		level = 0;
		b = ReachableNoneRecur(*iv1, *iv2, level);
		if(!b && level > 0)
			cout << *iv1 <<  " and " << *iv2 << " are FP" << endl;
		else if(!b)
			cout << *iv1 <<  " and " << *iv2 << " cannot reach" << endl;
		else
			cout << *iv1 <<  " and " << *iv2 << " are reachable" << endl;
	}

}
