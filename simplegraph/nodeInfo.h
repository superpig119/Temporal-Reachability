#include <vector>
#include <map>
#include "Conf.h"
#include <sstream>
#include <string>
#include <sstream>

using namespace std;

#ifndef NODEINFO_H_
#define NODEINFO_H_
typedef struct NODEINFO
{
	int ID;			//node's orginal ID
	map<int, int> mEdge;    //neighbor ID,1
	vector<int> vEdge;
	vector<int> vParent;
	int p;	//the number of parents that have topo level;
	vector<int> vCoor;
	int coorSum;
	int coorMax;
	vector<int> vUnreachable;
	vector<int> vMaxCoor;	//Max coordinate to reach
	int level;	//the topological level
	bool noOut;
}nodeInfo;
#endif
