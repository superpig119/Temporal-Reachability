#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    map<vector<int>, int> m;
    map<vector<int>, int>::iterator im;
    vector<int> v1;
    v1.push_back(3);
    v1.push_back(5);
    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    vector<int> v3;
    v3.push_back(4);
    v3.push_back(5);
    vector<int> v4;
    v4.push_back(2);
    v4.push_back(3);
    vector<int> v5;
    v5.push_back(2);
    v5.push_back(8);
    cout << "1" << endl;
    m[v1] = 1;
    m[v2] = 1;
    m[v3] = 1;
    m[v4] = 1;
    m[v5] = 1;

    vector<int>::iterator iv;
    
    cout << "2" << endl;
    for(im = m.begin(); im != m.end(); im++)
    {
        vector<int> vv = (*im).first;
 //       for(iv = ((*im).first).begin(); iv != ((*im).first).end(); iv++)
        for(iv = vv.begin(); iv != vv.end(); iv++)
        {
            cout << *iv << "\t";
        }
        cout << endl;
    }
    return 0;
}
