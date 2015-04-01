#include "Grid.h"

void Grid::buildGrid(int max)
{
	Conf cf;
	cf.readConf();
	int ninterval;
	ninterval = cf.ninterval;
	step = max / ninterval;

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
	
vector<int> Grid::getNodes(int x1, int x2, int y1, int y2)
{
	int n1 = x1 / step;
	int n2 = x2 / step;
	int m1 = y1 / step;
	int m2 = y2 / step;
	int i, j;
	cout << n1 << "\t" << n2 << "\t" << m1 << "\t" << m2 << endl;
	vector<int> vR;
	vector<nc>::iterator inc;
	for(i = n1; i <= n2; i++)
	{
		for(j = m1; j <= m2; j++)
		{
			vector<int> vtmp;
			vtmp.push_back(i);
			vtmp.push_back(j);
			for(inc = mgrid[vtmp].begin(); inc != mgrid[vtmp].end(); inc++)
			{
				vR.push_back((*inc).ID);
		//		cout << (*inc).ID << endl;
			}
		}
	}
	sort(vR.begin(), vR.end());
	return vR;
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
