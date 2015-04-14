#include <vector>
#include <map>
#include "Conf.h"
#include <sstream>

using namespace std;

#ifndef NODEINFO_H_
#define NODEINFO_H_
typedef struct NODEINFO
{
	int ID;			//node's orginal ID
	map<int, int> mEdge;    //neighbor ID,1
	vector<int> vCoor;
	vector<int> vUnreachable;
	vector<int> vMaxCoor;	//Max coordinate to reach
}nodeInfo;
#endif
