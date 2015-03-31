#include <vector>
#include <map>

using namespace std;

#ifndef NODEINFO_H_
#define NODEINFO_H_
typedef struct NODEINFO
{
	int ID;			//node's orginal ID
	map<int, int> mEdge;
	vector<int> vCoor;
	vector<int> vUnreachable;
	vector<int> vMaxCoor;	//Max coordinate to reach
}nodeInfo;
#endif
