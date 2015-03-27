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
			ni.lEdge.push_back(dNode);
		}
		vnode.push_back(ni);
	}
}

void SimpleGraph::findSCC()
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
//    testSCC();
}

void SimpleGraph::tarjan(int i, vector<int> &vDFN, int &dIndex, int &Stop, vector<int> &vLOW, vector<bool> &vInstack, stack<nodeInfo> &sNode, int &Bcnt, vector<int> &vBelong)//Tarjan 
{
	int j;
	vDFN[i]=vLOW[i]=++dIndex;//Index 时间戳 
	vInstack[i]=true;//标记入栈 
    sNode.push(vnode[i]);
	//Stap[++Stop]=i;//入栈 
//	for (edge *e=V[i];e;e=e->next)//枚举所有相连边 
	list<int>::iterator ilEdge;
    for(ilEdge = vnode[i].lEdge.begin(); ilEdge != vnode[i].lEdge.end(); ilEdge++)
	{
		//j=e->t;//临时变量 
        j = vnode[(*ilEdge)].ID;
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
            nodeInfo n = sNode.top();
            sNode.pop();
            j = n.ID;
			vInstack[j]=false;//标记出栈 
			vBelong[j]=Bcnt;//记录j所在的强连通分量编号 
		}
		while (j != i);//如果是当前元素,弹栈完成 
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
