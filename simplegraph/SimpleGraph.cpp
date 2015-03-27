#include "SimpleGraph.h"

void SimpleGraph::buildGraph(const char* fileName)
{
	ifstream infile(fileName);
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
		for(j = 0; j < edgeNum; j++)
		{
			infile >> dNode;
			ni.mEdge[dNode] = 1;
		}
		vnode.push_back(ni);
	}
}

bool SimpleGraph::findSCC()
{
	int i, Stop, Bcnt, dIndex;
	Stop = Bcnt=dIndex=0;
    vector<int> vDFN(vnode.size(), 0);
    vector<int> vLOW(vnode.size(), 0);
    vector<bool> vInstack(vnode.size(), false);
    vector<int> vBelong(vnode.size(), -1);
    stack<nodeInfo> sNode;
//	memset(DFN,0,sizeof(DFN));//标记为为搜索过 
	for (i = 0;i < vnode.size(); i++)
		if (!vDFN[i])
			tarjan(i, vDFN, dIndex, Stop, vLOW, vInstack, sNode, Bcnt, vBelong);
    for(i = 0; i< vnode.size(); i++)
    {
        msSCC[vBelong[i]].insert(i);
    }
	if(msSCC.size() == 1)
		return false;
	return true;
//    testSCC();
}

void SimpleGraph::tarjan(int i, vector<int> &vDFN, int &dIndex, int &Stop, vector<int> &vLOW, vector<bool> &vInstack, stack<nodeInfo> &sNode, int &Bcnt, vector<int> &vBelong) 
{
	int j;
	vDFN[i]=vLOW[i]=++dIndex; 
	vInstack[i]=true; 
    sNode.push(vnode[i]);
	map<int, int>::iterator imEdge;
    for(imEdge = vnode[i].mEdge.begin(); imEdge != vnode[i].mEdge.end(); imEdge++)
	{
        j = vnode[(*imEdge).first].ID;
		if (!vDFN[j])
		{
			tarjan(j, vDFN, dIndex, Stop, vLOW, vInstack, sNode, Bcnt, vBelong); 
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
            nodeInfo n = sNode.top();
            sNode.pop();
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
					if(vNode[(*imsSCC).first-1].mEdge.find(n2) == vNode[(*imsSCC).first-1].mEdge.end())
					{
						vNode[(*imsSCC).first-1].mEdge.insert(make_pair(n2, 1));
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

void SimpleGraph::testSCC()
{
    map<int, set<int> >::iterator imsSCC;
    set<int>::iterator is;
    for(imsSCC = msSCC.begin(); imsSCC != msSCC.end(); imsSCC++)
    {
        cout << "SCC " << (*imsSCC).first << ": ";
        for(is = (*imsSCC).second.begin(); is != (*imsSCC).second.end(); is++)        
            cout << *is << "\t";
        cout << endl;
	}
}

void SimpleGraph::testGraph()
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
