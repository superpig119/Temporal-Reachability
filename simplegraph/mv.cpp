#include <iostream>
#include <vector>
#include <map>

using namespace std;

class vCompare
{
public:
	bool operator()(const vector<int> &v1, const vector<int> &v2) const
	{
		vector<int>::const_iterator  iv1, iv2;
		for(iv1 = v1.begin(), iv2 = v2.begin(); iv1 != v1.end(); iv1++, iv2++)
		{
			if(*iv1 >= *iv2)
				break;
		}
		if(iv1 == v1.end())
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
    map<vector<int>, int, vCompare> mv;
    map<vector<int>, int, vCompare>::iterator imv;
    map<vector<int>, int, vCompare>::reverse_iterator rimv;
    vector<int>::iterator iv;

    vector<int> v1;
    v1.push_back(1);
    v1.push_back(4);
    vector<int> v2;
    v2.push_back(4);
    v2.push_back(1);
    vector<int> v3;
    v3.push_back(2);
    v3.push_back(2);
    vector<int> v4;
    v4.push_back(5);
    v4.push_back(5);
    vector<int> v5;
    v5.push_back(3);
    v5.push_back(0);
    vector<int> v6;
    v6.push_back(2);
    v6.push_back(9);
    mv[v4] = 0;
    mv[v1] = 1;
    mv[v2] = 2;
    mv[v3] = 3;
    mv[v5] = 4;
    mv[v6] = 5;
    
    for(imv = mv.begin(); imv != mv.end(); imv++)
    {
        vector<int> v = (*imv).first;
        for(iv = v.begin(); iv != v.end(); iv++)
            cout << *iv << "\t";
        cout << (*imv).second;
        cout << endl;
    }
    cout << "v1\t" <<   (*(mv.find(v1))).second << endl;
    cout << "v2\t" <<   (*(mv.find(v2))).second << endl;

    rimv = mv.rbegin();
    ++rimv;
    mv.erase(rimv.base());

    for(imv = mv.begin(); imv != mv.end(); imv++)
    {
        vector<int> v = (*imv).first;
        for(iv = v.begin(); iv != v.end(); iv++)
            cout << *iv << "\t";
        cout << (*imv).second;
        cout << endl;
    }

    cout << mv.size() << endl; 
    return 0;
}
