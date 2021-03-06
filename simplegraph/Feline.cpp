#include "Feline.h"
bool operator <(nodeInfo &n1, nodeInfo &n2)
{
	vector<int>::iterator iv1, iv2;
	if(n1.vCoor.size() > 3)
		if(n1.coorSum + n1.vCoor.size() - 2 >= n2.coorSum || n1.coorMax > n2.coorMax)
			return false;
	for(iv1 = n1.vCoor.begin(), iv2 = n2.vCoor.begin(); iv1 != n1.vCoor.end() && iv2 != n2.vCoor.end(); iv1++, iv2++)
	{
		if(*iv1 >= *iv2)
			return false;
	}
	return true;
}

bool vFPCompare(const pair<int,int> &v1, const pair<int,int> &v2)
{
	if(v1.second > v2.second)
		return true;
	else 
		return false;
}

void Feline::coorCreate()
{
	coorMax = vNode.size();
	topologicalOrdering();
//	xCoor();
	yCoor();
    outputCoor();
	topoLevel();
	vector<nodeInfo>::iterator ivnode;
	vector<int>::iterator ivp;
	
	bool RP = false;
	int fp;
	vector<int> vp(5, 99999999);
	int i = 0;
	int j;
	int lastFP = 999999999;
	bool noBetter = true;
	map<int, int> mFPNumber;
	map<int, int>::iterator imFP;
	while(1)
	{
		if(i++ > 50)
			break;
		noBetter = true;
		cout << "i:" << i << endl;
		Sample(mFPNumber, fp);
		cout << "fp number:" << fp << endl;
		cout << "mFPNumber size:" << mFPNumber.size() << endl;
		cout << "coordinate dimension:" << (*vNode.begin()).vCoor.size() << endl;
		if(fp == 0)
			break;
	    vector<pair<int, int> > vFP;	//Store the FP from the map to vector
	    vector<pair<int, int> >::iterator  ivFP;
		j = 0;
/*		while(fp >= lastFP && j < 5)
		{
			fp = 0;
			genTestSet();
			mFPNumber.clear();
			Sample(mFPNumber, fp);
			j++;
		}*/
		lastFP = fp;
//		if(i > 10)
//		{
/*			for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
			{
//				(*ivnode).vCoor.erase((*ivnode).vCoor.end() - 1);
				(*ivnode).vCoor.pop_back();
			}*/
//			FPRemoveFromParent(mFPNumber);
//		}
//		else
			newCoor();
	}
	cout << "i:" << i << endl;
}

void Feline::xCoor()
{
	vector<nodeInfo>::iterator ivnode;
	vector<int>::iterator iv;
	int i;
	for(i = 0; i < vNode.size(); i++)
	{
		mdStatic[i] = 0;
	}

	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		for(iv = (*ivnode).vEdge.begin(); iv != (*ivnode).vEdge.end(); iv++)
		{
			mdStatic[*iv]++;
		}
	}

	map<int, int> md(mdStatic);
	map<int, int>::iterator imd;
	queue<int> roots;
	for(imd = md.begin(); imd != md.end(); imd++)
	{
		if((*imd).second == 0)
		{
			roots.push((*imd).first);
		}
	}

	int x = 0;
	int n;
	while(!roots.empty())
	{
		n = roots.front();
		roots.pop();
		vNode[n].vCoor.push_back(x);
		x++;
		if(x % 10000 == 0)
			cout << x << endl;
		for(iv = vNode[n].vEdge.begin(); iv != vNode[n].vEdge.end(); iv++)
		{
			md[*iv]--;
			if(md[*iv] == 0)
			{
				roots.push(*iv);
			}
		}
	}
}

void Feline::yCoor()
{
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	vector<int>::iterator iv;
/*	int i;
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
	}*/

	map<int, int> md(mdStatic);
	map<int, int> roots;	//<x, sNum>
	map<int, int>::reverse_iterator iroots;	
	map<int, int>::iterator imd;
	for(imd = md.begin(); imd != md.end(); imd++)
	{
		if((*imd).second == 0)
			roots[vNode[(*imd).first].vCoor[0]] = vNode[(*imd).first].ID;
	}
	cout << "mroots size:" << roots.size() << endl;

	int y = 1;
	while(roots.size())
	{
		int u = (*(roots.rbegin())).second;
		iroots = roots.rbegin();
		roots.erase((*iroots).first);
		vNode[u].vCoor.push_back(y);
		vNode[u].coorSum += y;
		if(vNode[u].coorMax < y)
			vNode[u].coorMax = y;
		y++;
		if(y%10000==0)
			cout << y << endl;
		for(iv = vNode[u].vEdge.begin(); iv != vNode[u].vEdge.end(); iv++)
		{
			md[*iv]--;
			if(md[*iv] == 0)
			{
				roots[vNode[*iv].vCoor[0]] = *iv;
			}
		}
	}

	int j;
}

void Feline::topoLevel()
{
	cout << "Computing Topo Level" << endl;
	map<int,int> md(mdStatic);
	map<int,int>::iterator imd, imEdge;
	map<int, bool> mvisited;
	vector<int>::iterator iv;
	queue<int> qnode;
	for(imd = md.begin(); imd != md.end(); imd++)
	{
		if((*imd).second == 0)
		{
            qnode.push((*imd).first);
			vNode[(*imd).first].level = 0;
			mvisited[(*imd).first] = true;
//			for(imEdge = vNode[(*imd).first].mEdge.begin(); imEdge != vNode[(*imd).first].mEdge.end(); imEdge++)
			for(iv = vNode[(*imd).first].vEdge.begin(); iv != vNode[(*imd).first].vEdge.end(); iv++)
			{
//				vNode[(*imEdge).first].p++;
				vNode[*iv].p++;
//				if(vNode[(*imEdge).first].p == vNode[(*imEdge).first].vParent.size())
				if(vNode[*iv].p == vNode[*iv].vParent.size())
				{
					qnode.push(*iv);
					mvisited[*iv] = true;
					vNode[*iv].level = 1;
				}
			}
		}
	}

	int n;
	map<int, int>::iterator im;
	vector<int>::iterator ivp;
	while(!qnode.empty())
	{
		n = qnode.front();
		qnode.pop();
//		for(im = vNode[n].mEdge.begin(); im != vNode[n].mEdge.end(); im++)
		for(iv = vNode[n].vEdge.begin(); iv != vNode[n].vEdge.end(); iv++)
		{
			vNode[*iv].p++;
			if(vNode[*iv].p == vNode[*iv].vParent.size())
			{
				qnode.push(*iv);
				int max=0;
				for(ivp = vNode[*iv].vParent.begin(); ivp != vNode[*iv].vParent.end(); ivp++)
				{
					if(vNode[*ivp].level > max)
						max = vNode[*ivp].level;
				}
				vNode[*iv].level = max + 1;
			}
		}
	}


	
/*	while(!qnode.empty())
	{
		n = qnode.front();
		qnode.pop();
		for(im = vNode[n].mEdge.begin(); im != vNode[n].mEdge.end(); im++)
		{
			if(mvisited.find((*im).first) == mvisited.end())
			{
				qnode.push((*im).first);
				mvisited[(*im).first] = true;
			}
			if(vNode[n].level + 1 > vNode[(*im).first].level)
			{
				vNode[(*im).first].level = vNode[n].level + 1;
				qnode.push((*im).first);
			}
		}
	}*/
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
		vNode[TopoSort[i]].coorSum = cnt - i;
		if(vNode[TopoSort[i]].coorMax < cnt - i)
			vNode[TopoSort[i]].coorMax = cnt - i;
		vector<int> v;
		v.push_back(cnt - i);
		mvCoor[TopoSort[i]] = v;
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
	nodeInfo n = vNode[sNum];
	vector<int>::iterator iv;
	for(iv = n.vEdge.begin(); iv != n.vEdge.end(); iv++)
	{
		if(!visited[*iv])
		{
			vParent[*iv] = sNum;
			DFS(*iv, visited, time, vd, vf, vParent, cnt, TopoSort);
		}
	}
	time++;
	vf[sNum] = time;
	TopoSort[cnt++] = sNum;
}
	
void Feline::newCoor()
{
	int i, j;
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	map<int, int> md(mdStatic);//copy of mdStatic
    map<vector<int>, int, vCompare> mroots;   //coor,ID
    map<vector<int>, int, vCompare>::iterator imroots;   //coor,ID
    map<vector<int>, int, vCompare>::reverse_iterator rimroots;   //coor,ID
	map<int, int>::iterator imd;
    vector<int>::iterator ivi, iv;
    vector<int>::const_iterator icvi;
	for(imd = md.begin(); imd != md.end(); imd++)
	{
		if((*imd).second == 0)
		{
		/*	if(mroots.find(vNode[(*imd).first].vCoor) != mroots.end())
			{
				cout << "Conflict!" << endl;
				imroots = mroots.find(vNode[(*imd).first].vCoor);
				float m1 = 0;
				float m2 = 0;
				long long d1 = 0;
				long long d2 = 0;
				for(icvi = (*imroots).first.begin(); icvi != (*imroots).first.end(); icvi++)
				{
					m1 += *icvi;
					cout << *icvi << "\t";
				}
				for(icvi = (*imroots).first.begin(); icvi != (*imroots).first.end(); icvi++)
				{
					d1 += pow(*icvi-m1,2);
				}
				cout << "sum:" << m1<< endl;
				m1 = m1 / (*imroots).first.size();
				cout << "d:" << d1;
				cout << endl;

				for(ivi = vNode[(*imd).first].vCoor.begin(); ivi != vNode[(*imd).first].vCoor.end(); ivi++)
				{
					m2 += *ivi;
					cout << *ivi << "\t";
				}
				for(ivi = vNode[(*imd).first].vCoor.begin(); ivi != vNode[(*imd).first].vCoor.end(); ivi++)
				{
					d2 += pow(*ivi-m2,2);
				}
				cout << "sum:" << m2<< endl;
				m2 = m2 / (*imroots).first.size();
				cout << "d:" << d2;
				cout << endl;
			}*/
			mroots[vNode[(*imd).first].vCoor] = (*imd).first;

//            mroots[mvCoor[(*imd).first]] = (*imd).first;
		}
	}
	int c = 1;
	
	imroots = mroots.begin();
	bool f = false;

	while(mroots.size())
	{
//        int u = (*(mroots.rbegin())).second;
//        rimroots = mroots.rbegin();
 //       mroots.erase((++rimroots).base());
		imroots = mroots.begin();
		int u = (*imroots).second;
		mroots.erase(imroots);
        vNode[u].vCoor.push_back(c);
		vNode[u].coorSum += c;
		if(vNode[u].coorMax < c)
			vNode[u].coorMax = c;
//		mvCoor[u].push_back(c);
		c++;
		if(c%10000==0)
			cout << c << endl;
		for(iv = vNode[u].vEdge.begin(); iv != vNode[u].vEdge.end(); iv++)
		{
			md[vNode[*iv].ID]--;
			if(md[vNode[*iv].ID] == 0)
			{
//                mroots.insert(pair<vector<int>, int>(mvCoor[(*imEdge).first],vNode[(*imEdge).first].ID));
                mroots.insert(pair<vector<int>, int>(vNode[*iv].vCoor,*iv));
			}
		}
	}

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

void Feline::FPRemoveFromParent(map<int, int> &mFPNumber)
{
	cout << "Removing" << endl;
	map<int, int> md(mdStatic);//copy of mdStatic
    map<vector<int>, int, vCompare> mroots;   //coor,ID
    map<vector<int>, int, vCompare>::iterator imroots;   //coor,ID
    map<vector<int>, int, vCompare>::reverse_iterator rimroots;   //coor,ID
	map<int, int>::iterator imd;
	map<int, int>::iterator imFP;
	map<int, int>::iterator imEdge;
    vector<int>::iterator ivi, ivv;
    vector<int>::const_iterator icvi;
	map<int, bool> mvisited;
	for(imd = md.begin(); imd != md.end(); imd++)
	{
		if((*imd).second == 0)
		{
            mroots[vNode[(*imd).first].vCoor] = (*imd).first;
		}
	}
	int c = 0;
	
	cout << "mFPNumber size:" << mFPNumber.size() << endl;
	vector<pair<int, int> > vFP;	//Store the FP from the map to vector
	vector<pair<int, int> >::iterator  ivFP;
	for(imFP = mFPNumber.begin(); imFP != mFPNumber.end(); imFP++)
	{
		vFP.push_back(make_pair((*imFP).first, (*imFP).second));
	}
	cout << "vFP size:" << vFP.size() << endl;
	sort(vFP.begin(), vFP.end(), vFPCompare);	//sort,FP num desend
/*	for(ivFP = vFP.begin(); ivFP != vFP.end(); ivFP++)
	{
		cout << "Node number:" << (*ivFP).first << "\tFalse Positive number:" << (*ivFP).second << endl;
	}*/
	
	queue<int> qvisited;	//Queue for visiting the parents
	map<int, vector<int> > mvParent;	//level, nodeID
	map<int, vector<int> >::iterator imvParent;	
	vector<int>::iterator ivParent;
	int qn,sn;
	for(ivFP = vFP.begin(); ivFP != vFP.end(); ivFP++)
	{
		if(mvisited.find((*ivFP).first) != mvisited.end())
			continue;   //if already visited, then move on
		qvisited.push((*ivFP).first);
		mvisited[(*ivFP).first] = true;
        if(mvParent.find(vNode[(*ivFP).first].level) == mvParent.end())
        {
		    vector<int> v;
		    v.push_back((*ivFP).first);
    		mvParent[vNode[(*ivFP).first].level] = v;
        }
        else
            mvParent[vNode[(*ivFP).first].level].push_back((*ivFP).first);
		while(!qvisited.empty())
		{
			qn = qvisited.front();
			qvisited.pop();
			for(ivParent = vNode[qn].vParent.begin(); ivParent != vNode[qn].vParent.end(); ivParent++)
			{
				if(mvisited.find(*ivParent) == mvisited.end())
				{
					mvisited[(*ivParent)] = true;
					if(mvParent.find(vNode[*ivParent].level) == mvParent.end())
					{
						vector<int> vv;
						vv.push_back(*ivParent);
						mvParent[vNode[*ivParent].level] = vv;
					}
					else
						mvParent[vNode[*ivParent].level].push_back(*ivParent);
					if(md[*ivParent] != 0)
					{
						qvisited.push((*ivParent));
					}
				}
			}
		}
		for(imvParent = mvParent.begin(); imvParent != mvParent.end(); imvParent++)
		{
			for(ivv = (*imvParent).second.begin(); ivv != (*imvParent).second.end(); ivv++)
			{
				imroots = mroots.find(vNode[*ivv].vCoor);
				if(imroots != mroots.end())
				{
					mroots.erase(imroots);
				}
	            vNode[*ivv].vCoor.push_back(c);
	            vNode[*ivv].coorSum += c;
				if(vNode[*ivv].coorMax < c)
					vNode[*ivv].coorMax = c;
				for(imEdge = vNode[*ivv].mEdge.begin(); imEdge != vNode[*ivv].mEdge.end(); imEdge++)
				{
					md[vNode[(*imEdge).first].ID]--;
					if(md[vNode[(*imEdge).first].ID] == 0 && mvisited.find((*imEdge).first) == mvisited.end())
					{
						mroots.insert(pair<vector<int>, int>(vNode[(*imEdge).first].vCoor,vNode[(*imEdge).first].ID));
					}
				}
				c++;
				if(c%10000==0)
					cout << c << endl;
			}
		}
		mvParent.clear();
	}
	
	cout << "in root" << endl;
	while(mroots.size())
	{
        int u = (*(mroots.rbegin())).second;
        rimroots = mroots.rbegin();
        mroots.erase((++rimroots).base());
		if(mvisited.find(u) != mvisited.end())
		{
			continue;
		}
        mvisited[u] = true;
	    vNode[u].vCoor.push_back(c);
	    vNode[u].coorSum += c;
		if(vNode[u].coorMax < c)
			vNode[u].coorMax = c;
		c++;
		if(c%10000==0)
			cout << c << endl;
		for(imEdge = vNode[u].mEdge.begin(); imEdge != vNode[u].mEdge.end(); imEdge++)
		{
			md[vNode[(*imEdge).first].ID]--;
			if(md[vNode[(*imEdge).first].ID] == 0 && mvisited.find((*imEdge).first) == mvisited.end())
			{
                mroots.insert(pair<vector<int>, int>(vNode[(*imEdge).first].vCoor,vNode[(*imEdge).first].ID));
			}
		}
	}
	mFPNumber.clear();
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

bool Feline::ReachableNoneRecur(int s1, int s2, int &level, vector<unsigned> &visited, unsigned &queryid)
{
	queryid++;
	if(vNode[s1].noOut)
		return false;
 
	vector<int>::iterator iv;
	if(noRecur == 0)
    {
        if(vNode[s1] < vNode[s2] && vNode[s1].level < vNode[s2].level)
        {
    //        map<int, int> mvisited;
//			map<int, int>::iterator imEdge;
            queue<int> q;
            q.push(s1);
			visited[s1] = queryid;
            while(!q.empty())
            {
                level++;
                int nt = q.front();
                q.pop();
	//		    for(imEdge = vNode[nt].mEdge.begin(); imEdge != vNode[nt].mEdge.end(); imEdge++)
				for(iv = vNode[nt].vEdge.begin(); iv != vNode[nt].vEdge.end(); iv++)
                {
//                    if((*imEdge).first == s2)
					if(*iv == s2)
                        return true;
                    else
                    {
						if(visited[*iv] < queryid && vNode[*iv] <vNode[s2] && vNode[*iv].level < vNode[s2].level)
//                        if(visited[(*imEdge).first] < queryid && vNode[(*imEdge).first] < vNode[s2] && vNode[(*imEdge).first].level < vNode[s2].level)
                        {
//                            q.push((*imEdge).first);
							q.push(*iv);
                          //  mvisited[(*imEdge).first] = 1;
							//visited[(unsigned)((*imEdge).first)] = queryid;
							visited[(unsigned)*iv] = queryid;
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
		cout << "ID:\t" << (*ivnode).ID << endl;
		cout << "Topo Level:" << (*ivnode).level << endl;
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

void Feline::outputCoor()
{
    string s;
    stringstream ss;
    ss << (*vNode.begin()).vCoor.size();
    ss >> s;
    string name = "coor";
    name += s;
	ofstream ofile(s.c_str());
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

void Feline::testParent()
{
	vector<nodeInfo>::iterator ivnode;
    vector<int>::iterator ivParent;
    for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
    {
        cout << (*ivnode).ID << "'s Parents are:\t";
        for(ivParent = (*ivnode).vParent.begin(); ivParent != (*ivnode).vParent.end(); ivParent++)
        {
            cout << *ivParent << "\t";
        }
        cout << endl;
    }
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
	int ttest = vNode.size();
	mRandom.clear();
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
	vector<unsigned> visited(vNode.size(), 0);
	unsigned queryid = 0;
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
        bool b = ReachableNoneRecur(m1, m2, level, visited, queryid);
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
	
void Feline::outputStat(int d, float mis, float online, double duration)
{
	float Accuracy = 1 - (mis / mRandom.size());
	float FPrate = mis / online;
	float FPpercent = mis / mRandom.size();
	float onlineRate = online / mRandom.size();

    ofstream fACC("ACC", ofstream::app);
    fACC << d << "\t" << Accuracy << endl;
    fACC.close();

    ofstream fFPrate("FPrate", ofstream::app);
    fFPrate << d << "\t" << FPrate << endl;
    fFPrate.close();
    
	ofstream fFPpercent("FPpercent", ofstream::app);
    fFPpercent << d << "\t" << FPpercent << endl;
    fFPpercent.close();

    ofstream fonR("onR", ofstream::app);
    fonR << d << "\t" << onlineRate << endl;
    fonR.close();

    ofstream ftquery("tquery", ofstream::app);
    ftquery << d << "\t" << duration / mRandom.size() /CLOCKS_PER_SEC << endl;
    ftquery.close();
    
	ofstream ffpper("FPpercent", ofstream::app);
	ffpper << d << "\t" << FPpercent << endl;
		
    
	cout << "d:" << d << "\ttotal test:" << mRandom.size() << "\tMiss:" << mis << "\tFPRate:" <<  FPrate << "\tAcc Rate:" << Accuracy << "\tOnline Rate:" << onlineRate << "\tFPpercent:" << FPpercent << endl;
    cout << "Average query time:" << duration / mRandom.size() / CLOCKS_PER_SEC << endl;
}

void Feline::Sample(map<int,int> & mFPNumber, int &fp)
{
    int n = vNode.size();
    int n1, n2, i;
    int level = 0;
    float mis = 0;
    float online = 0;
    clock_t t1, t2;
    cout << "Sampleing:" << endl;
    
    noRecur = 0;
	ifstream ifn("Recur");
	ifn >> noRecur;
	ifn.close();
	
	mFPNumber.clear();
	int ttest = n;
    srand((unsigned)time(NULL));
	map<pair<int, int>, int >::iterator imR;
	genTestSet();
	ttest = mRandom.size();
	cout << "mRandom size:" << ttest << endl;
	vector<pair<int, int> > vp;
	vector<pair<int, int> >::iterator ivp;
	for(imR = mRandom.begin(); imR != mRandom.end(); imR++)
	{
		vp.push_back(make_pair((*imR).first.first, (*imR).first.second));
	}
	vector<unsigned> visited(vNode.size(), 0);
	unsigned queryid = 0;
		bool b;
	t1 = clock();
//	for(i = 0, imR = mRandom.begin(); i < ttest; i++, imR++)
	for(i = 0, ivp = vp.begin(); i < ttest; i++, ivp++)
    {
        level = 0;
//        int m1 = (*imR).first.first;
//        int m2 = (*imR).first.second;
		int m1 = (*ivp).first;
		int m2 = (*ivp).second;
		if(vNode[m1].vEdge.size() == 0 || vNode[m2].vParent.size() == 0 || vNode[m1].level >= vNode[m2].level)
			b = false;
		else
	        b = ReachableNoneRecur(m1, m2, level, visited, queryid);
        if(level >= 1 && !b) 
        {
            mis++;
	/*		if(mFPNumber.find(m2) == mFPNumber.end())
				mFPNumber[m2] = 1;
			else
				mFPNumber[m2] = mFPNumber[m2] + 1;*/
        }
        if(level >= 1)
        {
            online++;
        }
	}
	t2 = clock();
    double duration = (double)(t2 - t1);
	int dimension = vNode[0].vCoor.size();
	outputStat(dimension, mis, online, duration);
	fp = mis;
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
	//	b = ReachableNoneRecur(*iv1, *iv2, level);
		if(!b && level > 0)
			cout << *iv1 <<  " and " << *iv2 << " are FP" << endl;
		else if(!b)
			cout << *iv1 <<  " and " << *iv2 << " cannot reach" << endl;
		else
			cout << *iv1 <<  " and " << *iv2 << " are reachable" << endl;
	}

}
