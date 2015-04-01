#include "Conf.h"

void Conf::readConf()
{
	ifstream inConf("configure");
	inConf >> filename;
	inConf >> ninterval;
	inConf >> dimension;
}
