#include <iostream>
#include <map>
#include <vector>

using namespace std;

class vCompare
{
public:
	bool operator()(const int &v1, const int &v2) const
	{
		if(v1 < v2)
			return false;
		else
			return true;
	}
};

int main()
{
    map<int, int, vCompare> m;
    map<int, int, vCompare>::iterator im;
	m[1]=2;
	m[2]=2;

	for(im = m.begin(); im != m.end(); im++)
		cout << (*im).first << endl;

    return 0;
}
