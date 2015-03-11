#include "Feline.h"

int main()
{
/*	TGraph TG;
	TG.buildGraph(fileName.c_str());*/
	Feline F;
	string fileName = "../data/data3";
	F.buildGraph(fileName.c_str());
	F.coorCreate();
	//TG.findSCC();
	return 0;	
}
