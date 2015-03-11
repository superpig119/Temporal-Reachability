#include "TransformedGraph.h"

bool nodeTimeCompare(node n1, node n2)
{
	return (n1.ni.temporalID < n2.ni.temporalID);
}

void TGraph::buildGraph(const char* fileName)
{
	countInOut(fileName);
	createNodes();
	addEdges(fileName);
}
	
void TGraph::countInOut(const char* fileName)
{
	ifstream infile(fileName);
	int lineNum;
	infile >> lineNum;
	nodeNum = lineNum;
	int edgeNum;
	int i, j;
	int sNode, dNode;
	int ts, te;

	for(i = 0; i < lineNum; i++)
	{
		infile >> sNode;
		infile >> edgeNum;
		for(j = 0; j < edgeNum; j++)
		{
			infile >> dNode >> ts >> te;
			mmOutTime[sNode][ts] = true;
			mmInTime[dNode][te] = true;
		}
	}
	infile.close();
//	testCountInOut(mmInTime, mmOutTime);
}
	
void TGraph::createNodes()
{
	map<int, bool>::iterator im;
	int i;
	int sNum = 0;	//serial number
	for(i = 0; i < nodeNum; i++)
	{
		vector<node> vntmp;
		vector<node>::iterator ivntmp1, ivntmp2;
		for(im = mmInTime[i].begin(); im != mmInTime[i].end(); im++)
		{
			node n;
			n.ni.ID = i;
			n.ni.temporalID = (*im).first;
			n.ni.sNum = sNum;
			mmInSnum[i][(*im).first] = sNum;
			sNum++;
			n.ni.nodeType = 0;
			vnode.push_back(n);
			vntmp.push_back(n);
			if(im != mmInTime[i].begin())	//create edge type 1
			{
				edgeInfo ei;
				ei.dNode = n.ni;
				ei.edgeType = 1;
				vnode[sNum - 2].lEdge.push_back(ei);
			}
		}
		for(im = mmOutTime[i].begin(); im != mmOutTime[i].end(); im++)
		{
			node n;
			n.ni.ID = i;
			n.ni.temporalID = (*im).first;
			n.ni.sNum = sNum;
			mmOutSnum[i][(*im).first] = sNum;
			sNum++;
			n.ni.nodeType = 1;
			vnode.push_back(n);
			vntmp.push_back(n);
			if(im != mmOutTime[i].begin())
			{
				edgeInfo ei;
				ei.dNode = n.ni;
				ei.edgeType = 1;
				vnode[sNum - 2].lEdge.push_back(ei);
			}
		}
		std::sort(vntmp.begin(), vntmp.end(), nodeTimeCompare);	//create edge type 2
		for(ivntmp1 = vntmp.begin(); ivntmp1 != vntmp.end() - 1; ivntmp1++)
		{
			ivntmp2 = ivntmp1 + 1;
			if((*ivntmp1).ni.nodeType == 0 && (*ivntmp2).ni.nodeType == 1)
			{
				edgeInfo ei;
				ei.dNode = (*ivntmp2).ni;
				ei.edgeType = 2;
				vnode[(*ivntmp1).ni.sNum].lEdge.push_back(ei);
			}
		}
	}
//	testNodes();
}
	
void TGraph::addEdges(const char* fileName)
{
	ifstream infile(fileName);
	int lineNum;
	infile >> lineNum;
	nodeNum = lineNum;
	int edgeNum;
	int i, j;
	int sNode, dNode;
	int ts, te;
	node ns, nd;

	for(i = 0; i < lineNum; i++)
	{
		infile >> sNode;
		infile >> edgeNum;
		for(j = 0; j < edgeNum; j++)
		{
			infile >> dNode >> ts >> te;
			
			ns = vnode[mmOutSnum[sNode][ts]];
			nd = vnode[mmInSnum[dNode][te]];
			edgeInfo ei;
			ei.dNode = nd.ni;
			ei.sTime = ts;
			ei.eTime = te;
			ei.edgeType = 0;
			vnode[mmOutSnum[sNode][ts]].lEdge.push_back(ei);
		}
	}
	infile.close();
	testNodes();
}

void TGraph::tarjan(int i, vector<int> &vDFN, int &dIndex, int &Stop, vector<int> &vLOW, vector<bool> &vInstack, stack<node> &sNode, int &Bcnt, vector<int> &vBelong)//Tarjan 
{
	int j;
	vDFN[i]=vLOW[i]=++dIndex;//Index 时间戳 
	vInstack[i]=true;//标记入栈 
    sNode.push(vnode[i]);
	//Stap[++Stop]=i;//入栈 
    list<edgeInfo>::iterator ilEdge;
//	for (edge *e=V[i];e;e=e->next)//枚举所有相连边 
    for(ilEdge = vnode[i].lEdge.begin(); ilEdge != vnode[i].lEdge.end(); ilEdge++)
	{
		//j=e->t;//临时变量 
        j = (*ilEdge).dNode.sNum;
		if (!vDFN[j])//j没有被搜索过 
		{
			tarjan(j, vDFN, dIndex, Stop, vLOW, vInstack, sNode, Bcnt, vBelong);//递归搜索j 
			if (vLOW[j] < vLOW[i])//回溯中发现j找到了更老的时间戳 
				vLOW[i]= vLOW[j];//更新能达到老时间戳 
		}
		else if (vInstack[j] && vDFN[j] < vLOW[i])//如果已经印有时间戳 且 时间戳比较小,则有环 
			vLOW[i] = vDFN[j];//当前记录可追溯时间戳更新 
	}
	if (vDFN[i] == vLOW[i])//可追溯最老是自己,表明自己是当前强连通分量的栈底 
	{
		Bcnt++;//强连通分量数增加 
		do
		{
		//	j=Stap[Stop--];//出栈顶元素 
            node n = sNode.top();
            sNode.pop();
            j = n.ni.sNum;
			vInstack[j]=false;//标记出栈 
			vBelong[j]=Bcnt;//记录j所在的强连通分量编号 
		}
		while (j != i);//如果是当前元素,弹栈完成 
	}
}
void TGraph::findSCC()
{
	int i, Stop, Bcnt, dIndex;
	Stop = Bcnt=dIndex=0;
    vector<int> vDFN(vnode.size(), 0);
    vector<int> vLOW(vnode.size(), 0);
    vector<bool> vInstack(vnode.size(), false);
    vector<int> vBelong(vnode.size(), -1);
    stack<node> sNode;
//	memset(DFN,0,sizeof(DFN));//标记为为搜索过 
	for (i = 0;i < vnode.size(); i++)
		if (!vDFN[i])
			tarjan(i, vDFN, dIndex, Stop, vLOW, vInstack, sNode, Bcnt, vBelong);
    for(i = 0; i< vnode.size(); i++)
    {
        msSCC[vBelong[i]].insert(i);
    }
    
//    testSCC();
}

void TGraph::testSCC()
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
	
void TGraph::testCountInOut()
{
	map<int, bool>::iterator im;
	cout << "0 in time" << endl;
	for(im = mmInTime[0].begin(); im != mmInTime[0].end(); im++)
	{
		cout << (*im).first << "\t";
	}
	cout << endl;
	cout << "200 out time:" << endl;
	for(im = mmOutTime[200].begin(); im != mmOutTime[200].end(); im++)
	{
		cout << (*im).first << "\t";
	}
	cout << endl;
}
	
void TGraph::testNodes()
{
	vector<node>::iterator ivnode;
	list<edgeInfo>::iterator ilEdge;
	cout << "ID\ttemporalID\tsNum\tnodeType" << endl;
	for(ivnode = vnode.begin(); ivnode != vnode.end(); ivnode++)
	{
		cout << "ID:\t" << (*ivnode).ni.ID << "\t" << (*ivnode).ni.temporalID << "\t" << (*ivnode).ni.sNum << "\t" << (*ivnode).ni.nodeType << endl;
		cout << "edges:";
		for(ilEdge = (*ivnode).lEdge.begin(); ilEdge != (*ivnode).lEdge.end(); ilEdge++)
		{
			cout << "\t" << (*ilEdge).dNode.temporalID << "\t" << (*ilEdge).edgeType;
		}
		cout << endl;
	}
}
