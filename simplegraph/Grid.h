#include <fstream>
#include <iostream>
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

	void printGridCoor(vector<int> v);
	void showGrid();
	void showGridInfo();

	map<vector<int>, vector<nc> > mgrid;	//coordinate,nc set
	vector<nodeInfo> vNode;
};
