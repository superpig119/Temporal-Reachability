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
	if(F.Reachable(0, 5))
		cout << "Reachable!" << endl;
	else
		cout << "Not Reachable!" << endl;

	//TG.findSCC();
	return 0;	
}
