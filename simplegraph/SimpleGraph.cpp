#include "SimpleGraph.h"

int SimpleGraph::buildGraph()
{
	Conf cf;
	cf.readConf();
	ifstream infile(cf.filename.c_str());
	if(!infile)
    {
        cout << "There is no data file named " << cf.filename << endl;
        return -1;
    }
    int lineNum;
	infile >> lineNum;
	int edgeNum, sNode, dNode;
	int i, j;

	for(i = 0; i < lineNum; i++)
	{
		infile >> sNode;
		infile >> edgeNum;
		nodeInfo ni;
		ni.ID = sNode;
		ni.level = -1;
		ni.coorSum = 0;
		ni.coorMax = 0;

		if(edgeNum == 0)
			ni.noOut = true;
		else
			ni.noOut = false;
		
		for(j = 0; j < edgeNum; j++)
		{
			infile >> dNode;
			ni.mEdge[dNode] = 1;
			ni.vEdge.push_back(dNode);
		}
		ni.p = 0;
		vNode.push_back(ni);
	}

	infile.clear();
	infile.seekg(ios_base::beg);
	infile >> lineNum;
	for(i = 0; i < lineNum; i++)
	{
		infile >> sNode;
		infile >> edgeNum;
		for(j = 0; j < edgeNum; j++)
		{
			infile >> dNode;
			vNode[dNode].vParent.push_back(sNode);
		}
	}
    
    return 0;
}

bool SimpleGraph::findSCC()
{
	int i, Stop, Bcnt, dIndex;
	Stop = Bcnt=dIndex=0;
    vector<int> vDFN(vnode.size(), 0);
    vector<int> vLOW(vnode.size(), 0);
    vector<bool> vInstack(vnode.size(), false);
    vector<int> vBelong(vnode.size(), -1);
//    stack<nodeInfo> sNode;
    vector<nodeInfo> vsNode;
//	memset(DFN,0,sizeof(DFN));//标记为为搜索过 
	for (i = 0;i < vnode.size(); i++)
		if (!vDFN[i])
			tarjan(i, vDFN, dIndex, Stop, vLOW, vInstack, vsNode, Bcnt, vBelong);
    for(i = 0; i< vnode.size(); i++)
    {
        msSCC[vBelong[i]].insert(i);
    }
		cout << "msSCC size:" << msSCC.size() << endl;
	if(msSCC.size() == vnode.size())
	{
		return false;
	}
	return true;
//    testSCC();
}

void SimpleGraph::tarjan(int i, vector<int> &vDFN, int &dIndex, int &Stop, vector<int> &vLOW, vector<bool> &vInstack, vector<nodeInfo> &vsNode, int &Bcnt, vector<int> &vBelong) 
{
	int j;
	vDFN[i]=vLOW[i]=++dIndex; 
	vInstack[i]=true; 
    vsNode.push_back(vnode[i]);
	map<int, int>::iterator imEdge;
    for(imEdge = vnode[i].mEdge.begin(); imEdge != vnode[i].mEdge.end(); imEdge++)
	{
        j = vnode[(*imEdge).first].ID;
		if (!vDFN[j])
		{
			tarjan(j, vDFN, dIndex, Stop, vLOW, vInstack, vsNode, Bcnt, vBelong); 
			if (vLOW[j] < vLOW[i])
				vLOW[i]= vLOW[j];
		}
		else if (vInstack[j] && vDFN[j] < vLOW[i])
			vLOW[i] = vDFN[j];
	}
	if (vDFN[i] == vLOW[i]) 
	{
		Bcnt++;
		do
		{
            nodeInfo n = vsNode[vsNode.size() - 1];
            //sNode.pop();
            vsNode.pop_back();
            j = n.ID;
			vInstack[j]=false; 
			vBelong[j]=Bcnt;
		}
		while (j != i);
	}
}

void SimpleGraph::condense()
{
	if(hasSCC)
	{
		vector<nodeInfo>::iterator ivnode;
		map<int, int>::iterator imEdge;
		map<int, set<int> >::iterator imsSCC;
		set<int>::iterator is;
		int n = 0;
		for(imsSCC = msSCC.begin(); imsSCC != msSCC.end(); imsSCC++, n++)
		{
			nodeInfo ni;
			ni.ID = n;
			for(is = (*imsSCC).second.begin(); is != (*imsSCC).second.end(); is++)        
			{
				mOtoN[*is] = (*imsSCC).first;
			}
			vNode.push_back(ni);
		}
        
		for(imsSCC = msSCC.begin(); imsSCC != msSCC.end(); imsSCC++)
		{
			for(is = (*imsSCC).second.begin(); is != (*imsSCC).second.end(); is++)        
			{   
				for(imEdge = vnode[(*is)].mEdge.begin(); imEdge != vnode[(*is)].mEdge.end(); imEdge++)
				{
					int n2 = mOtoN[(*imEdge).first];
					if(vNode[(*imsSCC).first-1].mEdge.find(n2) == vNode[(*imsSCC).first-1].mEdge.end() && n2 != (*imsSCC).first)
					{
						vNode[(*imsSCC).first-1].mEdge.insert(make_pair(n2 - 1, 1));
					}
				}
			}
		}
	}
	else
	{
		vNode = vnode;
	}
}

void SimpleGraph::reachBFS()
{
    int i;
    int n = vNode.size();
    map<int, bool> mVisited;
    vector<vector<int> > vvNeighbor;
    vector<int>::iterator iv;
    int count = 0;
    for(i = 0; i < n; i++)
    {
        mVisited[i] = false;
        vector<int> neighbor;
        vvNeighbor.push_back(neighbor);
    }
    for(i = 0; i < n; i++)
    {
        if(!mVisited[i])
            BFS(i, mVisited, vvNeighbor, count);
    }
    for(i = 0; i < n; i++)
    {
        cout << i << "'s reachable:" << endl;
        for(iv = vvNeighbor[i].begin(); iv !=vvNeighbor[i].end(); iv++)
            cout << *iv << "\t";
        cout << endl;
    }
}
    
void SimpleGraph::BFS(int i, map<int, bool> &mVisited, vector<vector<int> > &vvNeighbor, int &count)
{
    if(vNode[i].mEdge.size() == 0)
    {
        count++;
        cout << "working on " << i << "\t" << count << endl;
        mVisited[i] = true;
    }
    else
    {
        map<int, int>::iterator imEdge;
        vector<int>::iterator iv;
        for(imEdge = vNode[i].mEdge.begin(); imEdge != vNode[i].mEdge.end(); imEdge++)
        {
            if(!mVisited[(*imEdge).first])
            {
                BFS((*imEdge).first, mVisited, vvNeighbor, count);
            }
            vvNeighbor[i].push_back((*imEdge).first);
            for(iv = vvNeighbor[(*imEdge).first].begin(); iv != vvNeighbor[(*imEdge).first].end(); iv++)
            {
                vvNeighbor[i].push_back(*iv);
            }
            mVisited[(*imEdge).first] = true;
        }
        mVisited[i] = true;
        count++;
        cout << "working on " << i << "\t" << count << endl;
        if(vvNeighbor[i].size())
        {
            sort(vvNeighbor[i].begin(), vvNeighbor[i].end());
        }
    }
}

void SimpleGraph::testSCC()
{
    map<int, set<int> >::iterator imsSCC;
    set<int>::iterator is;
    for(imsSCC = msSCC.begin(); imsSCC != msSCC.end(); imsSCC++)
    {
        cout << "SCC " << (*imsSCC).first - 1<< ": ";
        for(is = (*imsSCC).second.begin(); is != (*imsSCC).second.end(); is++)        
            cout << *is << "\t";
        cout << endl;
	}
}

void SimpleGraph::testGraph(vector<nodeInfo> &vNode)
{
	cout << vNode.size() << endl;
	vector<nodeInfo>::iterator ivnode;
	map<int, int>::iterator imEdge;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		cout << "node:" << (*ivnode).ID << endl << "edges:\t";
		for(imEdge = (*ivnode).mEdge.begin(); imEdge != (*ivnode).mEdge.end(); imEdge++)
		{
			cout << (*imEdge).first << "\t";
		}
		cout << endl;
	}
}
