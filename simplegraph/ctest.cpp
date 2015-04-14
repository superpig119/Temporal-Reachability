#include <iostream>
#include <map>
#include <vector>

using namespace std;

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
		if(iv1 == v1.end() || iv2 == v2.end())
			return true;
		else
		{
			int t1 = 0;
			int	t2 = 0;
			for(iv1 = v1.begin(); iv1 != v1.end(); iv1++)
				t1 += (*iv1);
			for(iv2 = v2.begin(); iv2 != v2.end(); iv2++)
				t2 += (*iv2);
			if(t1 <= t2)
				return true;
			else
				return false;
		}
	}
};

int main()
{
	vector<int> a,b,c;
	a.push_back(2);
	a.push_back(2);
	b.push_back(3);
	b.push_back(1);
	c.push_back(4);
	c.push_back(4);

	map<vector<int>, int, vCompare> m;
	map<vector<int>, int, vCompare>::iterator im;
	m[a] = 1;
	m[b] = 2;
	m[c] = 3;

	for(im = m.begin(); im != m.end(); im++)
		cout << (*im).second << endl;

	cout << m[a] << "\t" << m[b] << endl;

	return 0;
}
