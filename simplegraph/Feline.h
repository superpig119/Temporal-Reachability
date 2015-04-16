#include "SimpleGraph.h"
#include "Grid.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <time.h>

class Feline : public SimpleGraph
{
public:
	void coorCreate();
	void topologicalOrdering();
	void yCoor();
	void DFSTravel(int &cnt, vector<int> &TopoSort);
	void DFS(int sNum, vector<bool> &visited, int &time, vector<int> &vd, vector<int> &vf, vector<int> &vParent, int &cnt, vector<int> &TopoSort);
	void highDCoor();
	bool Reachable(int s1, int s2, int &level);
	
	void findMaxCoor();
    void postRoot(int i, map<int, bool> &mVisited);
	void findFP();

	void testNode();
    void showEdges();	
	void outputEdges();	//output edge file
	void outputNodes();	//output coordiante file

    void randomTest();

	map<int, int> mdStatic;	//in-neighbor number
	int nFP;			//false positive number
	int d;
	map<int, set<int> > msFP;
	int coorMax;
    map<int, int> mTopo;//Topo order
	int noRecur;

//	map<int, set<int> > mheads;//out-neighbors
};

bool operator <(nodeInfo &n1, nodeInfo &n2);
bool coorCompare(nodeInfo n1, nodeInfo n2);

class vCompare
{
public:
	bool operator()(const vector<int> &v1, const vector<int> &v2) const
	{
		vector<int>::const_iterator  iv1, iv2;
		for(iv1 = v1.begin(), iv2 = v2.begin(); iv1 != v1.end() && iv2 != v2.end(); iv1++, iv2++)
		{
			if(*iv1 >= *iv2)
				break;
		}
		if((iv1 == v1.end() || iv2 == v2.end()))
			return true;
		else
		{
			int t1 = 0;
			int	t2 = 0;
//			int t1max =	0;
//			int	t2max = 0;
//			int t1min = 100000000;
//			int	t2min = 100000000;
			for(iv1 = v1.begin(); iv1 != v1.end(); iv1++)
			{
//				if(*iv1 < t1min)
//					t1min = *iv1;
//				if(*iv1 > t1max)
//					t1max = *iv1;
				t1 += (*iv1);
			}
			for(iv2 = v2.begin(); iv2 != v2.end(); iv2++)
			{
//				if(*iv2 < t2min)
//					t2min = *iv2;
//				if(*iv2 > t2max)
//					t2max = *iv2;
				t2 += (*iv2);
			}
				
			if(t1 < t2)
				return true;
			else if(t1==t2)
			{
				if(v1[0] < v2[0])
					return true;
				else 
					return false;
			}


/*			else if(t1 == t2)
			{
				int t1ex = t1max-t1min;
				int t2ex = t2max-t2min;
				if(t1ex  > t2ex)
					return true;
				else if (t1ex == t2ex)
				{
					if(v1[0] < v2[0])
						return true;
					else 
						return false;
				}
				else
					return false;
			}*/
			else	//t1>t2
				return false;
		}
	}
};
