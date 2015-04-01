#include <fstream>
#include <string>

using namespace std;

#ifndef CONF_H_
#define CONF_H_
class Conf
{
public:
	void readConf();

	string filename;
	int ninterval;
	int dimension;
};
#endif
