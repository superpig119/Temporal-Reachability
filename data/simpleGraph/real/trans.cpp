#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

main()
{
	string filename = "cit-Patents.txt";
	ifstream infile(filename.c_str());
	ofstream outfile(("data"+filename).c_str());
	
	stringstream ss;
	map<int, int> mConvert;
	map<int, vector<int> > mGraph;
	vector<int>::iterator iv;
	int s1, s2;
	int n = 0;
	while(infile >> s1 && infile >> s2)
	{
		if(mConvert.find(s2) == mConvert.end())
		{
			mConvert[s2] = n;
			n++;
		}

		if(mConvert.find(s1) == mConvert.end())
		{
			mConvert[s1] = n;
			vector<int> vNeighbor;
			vNeighbor.push_back(mConvert[s2]);
			mGraph[n] = vNeighbor;
			n++;
		}
		else
		{
			mGraph[mConvert[s1]].push_back(mConvert[s2]);
		}
	}
	infile.close();

	outfile << mConvert.size() << endl;
	int i = 0;
	for(i = 0; i < mConvert.size(); i++)
	{
		if(mGraph.find(i) == mGraph.end())
		{
			outfile << i << "\t" << 0 << endl;
		}
		else
		{
			outfile << i << "\t" << mGraph[i].size();
			for(iv = mGraph[i].begin(); iv != mGraph[i].end(); iv++)
			{
				outfile << "\t" << *iv;
			}
			outfile << endl;
		}
	}
	outfile.close();
}
