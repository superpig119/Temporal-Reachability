#include "Feline.h"

int main()
{
/*	TGraph TG;
	TG.buildGraph(fileName.c_str());*/
	ifstream infile("filename");
	Feline F;
	string fileName;
	infile >> fileName;
	F.buildGraph(fileName.c_str());
	F.coorCreate();
	//TG.findSCC();
	return 0;	
}
