#include "SimpleGraph.h"
#include "Grid.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <time.h>
#include <queue>
#include <stack>
#include <algorithm>

class Feline : public SimpleGraph
{
public:
	void coorCreate();
	void topologicalOrdering();
	void yCoor();
	void DFSTravel(int &cnt, vector<int> &TopoSort);
	void DFS(int sNum, vector<bool> &visited, int &time, vector<int> &vd, vector<int> &vf, vector<int> &vParent, int &cnt, vector<int> &TopoSort);
	void topoLevel();
	void highDCoor();
	void highDCoorv2();
	void newCoor();
	bool Reachable(int s1, int s2, int &level);
    bool ReachableNoneRecur(int s1, int s2, int &level);
	void Sample(map<int,int> &mFPNumber, int &fp);
	void FPRemoveFromParent(map<int, int> &mFPNumber);
	
	void findOptD();
	void findMaxCoor();
    void postRoot(int i, map<int, bool> &mVisited);
	void findFP();

	int EditDistance(vector<int> &v1, vector<int> &v2);
	float EucliDistance(vector<int> &v1, vector<int> &v2);
	int Diff(vector<int> &v1, vector<int> &v2);
	int LCS(vector<int> &v1, vector<int> &v2);

	void testNode();
    void testParent();
    void showEdges();	
	void outputEdges();	//output edge file
	void outputNodes();	//output coordiante file
    void outputCoor();
	void outputStat(int d, float mis, float online, double duration);

	void testD();
	void testReachable();

	void genTestSet();
    void randomTest();

	map<int, int> mdStatic;	//in-neighbor number
	int nFP;			//false positive number
	int d;
	map<int, set<int> > msFP;
	int coorMax;
    map<int, int> mTopo;//Topo order
	int noRecur;
	vector<int> dp, dq; //coordinates for neighbor dimensions
	map<pair<int, int>, int > mRandom;
	map<int, vector<int> > mvCoor;	//Store all the historical coor
};

bool operator <(nodeInfo &n1, nodeInfo &n2);
bool coorCompare(nodeInfo n1, nodeInfo n2);
bool vFPCompare(const pair<int,int> &v1, const pair<int,int> &v2);

class vCompare
{
public:
	bool operator()(const vector<int> &v1, const vector<int> &v2) const	//false:v2,v2	true:v1,v2
	{	
		vector<int>::const_iterator  iv1, iv2;	
		int t1 = 0;
		int	t2 = 0;
		bool f = true;
		int min1, min2 = 10000000;
		for(iv1 = v1.begin(), iv2 = v2.begin(); iv1 != v1.end() && iv2 != v2.end(); iv1++, iv2++)
		{
			if(*iv1 < min1)
				min1 = *iv1;
			if(*iv2 < min2)
				min2 = *iv2;
			t1 += *iv1;
			t2 += *iv2;
			if(*iv1 >= *iv2)
				f = false;	//v1 is not smaller than v2
		}

		if(f)	//phase1:v1 is smaller than v2, then v2 smaller than v1 in tree to be earlier retrieved
			return false;
		else	//when ki is not comparable
		{
			if(t1 > t2)	//phase2:compare sum
				return true;
			else if(t1 == t2)	//phase3:compare deviation
			{
				float m1, m2;
				m1 = t1 / v1.size();
				m2 = t2 / v2.size();
				float d1 = 0;
				float d2 = 0;
				for(iv1 = v1.begin(); iv1 != v1.end(); iv1++)
				{
					d1 += pow(*iv1 - m1, 2);
				}

				for(iv2 = v2.begin(); iv2 != v2.end(); iv2++)
				{
					d2 += pow(*iv2 - m2, 2);
				}
				
				if(d1 > d2)
				{
					return true;
				}
				else if(d1 == d2)
				{
					if(min1 > min2)
						return true;
					else if(min1 == min2)
					{
						if(v1[v1.size() - 1] > v2[v2.size() - 1])
							return true;
						else
							return false;
					}
					else//min1 < min2
						return false;
				}
				else	//d1 < d2
					return false;
			}
			else	//t1<t2
				return false;
		}
	}
};

