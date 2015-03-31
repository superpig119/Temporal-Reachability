#include "Grid.h"

void Grid::buildGrid(int max)
{
	ifstream ininterval("ninterval");
	int ninterval;
	ininterval >> ninterval;
	int step = max / ninterval;

	vector<nodeInfo>::iterator ivnode;
	vector<int>::iterator ivCoor;
	for(ivnode = vNode.begin(); ivnode != vNode.end(); ivnode++)
	{
		vector<int> vTmp;
		for(ivCoor = (*ivnode).vCoor.begin(); ivCoor != (*ivnode).vCoor.end(); ivCoor++)
		{
			vTmp.push_back((*ivCoor) / step);
		}
		nc n;
		n.ID = (*ivnode).ID;
		n.vCoor = (*ivnode).vCoor;
		mgrid[vTmp].push_back(n);
	}
}
	
void Grid::showGrid()
{
	map<vector<int>, vector<nc> >::iterator igrid;	
	vector<nc>::iterator inc;
	vector<int>::iterator ivCoor, ivc;
	for(igrid = mgrid.begin(); igrid != mgrid.end(); igrid++)
	{
		printGridCoor((*igrid).first);
		cout << ":" << endl;
		for(inc = (*igrid).second.begin(); inc != (*igrid).second.end(); inc++)
		{
			cout << (*inc).ID;
			for(ivCoor = (*inc).vCoor.begin(); ivCoor != (*inc).vCoor.end(); ivCoor++)
				cout << "\t" << *ivCoor;
			cout << endl;
		}
	}
}

void Grid::printGridCoor(vector<int> v)
{
	vector<int>::iterator ivc;
	for(ivc = v.begin(); ivc != v.end(); ivc++)
	{
		cout << *ivc << ".";
	}
}

void Grid::showGridInfo()
{
	map<vector<int>, vector<nc> >::iterator igrid;	
	vector<int>::iterator ivc;
	for(igrid = mgrid.begin(); igrid != mgrid.end(); igrid++)
	{
		printGridCoor((*igrid).first);
		cout << ":" << (*igrid).second.size() << endl;
	}

}
