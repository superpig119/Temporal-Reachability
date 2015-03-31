#include <fstream>
#include <iostream>
#include <algorithm>
#include "nodeInfo.h"

using namespace std;

typedef struct NC
{
	int ID;
	vector<int> vCoor;
}nc;

class Grid
{
public:
	void buildGrid(int max);
	vector<int> getNodes(int x1, int x2, int y1, int y2);

	void printGridCoor(vector<int> v);
	void showGrid();
	void showGridInfo();

	int step;

	map<vector<int>, vector<nc> > mgrid;	//coordinate,nc set
	vector<nodeInfo> vNode;
};
