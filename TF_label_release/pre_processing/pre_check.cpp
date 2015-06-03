

#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <stack>
#include <time.h>
#include "runtimecounter.h"
using namespace std;

const long int BLK_SZ = 4194304;  //1024*1024*4 sizeof blk for I/O
const int SZ_VERTEX = sizeof(int);
const int VERTEX_PER_BLK = BLK_SZ/SZ_VERTEX;
typedef int vertex_id;

char* read_buff_1;

const int K = 1;
const int max_round=15;
vector<int> SLin[max_round], SLout[max_round];
vector<int> deleV[max_round];
vector<int> startSLout[max_round], startSLin[max_round];
vector<int> inH, outH;
vector<int> * SL;

int **SLin1,**SLout1,**deleV1,**startSLout1,**startSLin1;
int vertexN, edgeN;
int *edge, *start, *startR, *edgeR, *ind, *outd, *indice;
bool *ficout, *ficin;
int *Q, *L, *R, *Lnew, *Qnew, *dag;
int Hdegree[K], level,round;
char s[50],label_name[50];
int tgraph,tgraph2;
int pt,pt2;
int rN[max_round];
Runtimecounter rt;
stack<int> dS;

static void usage() {
	cout << "\nUsage:\n"
		"	TF-Label [-h] [-r resultfile] filename\n"
		"Description:\n"
		"	-h	Print the help message.\n"
		"	-i	Set the index filename.\n"
		"	filename	The graph file(DAG).\n"
		<< endl;
}

void reverse() {
	int sum = 0;
	for (int i = 0; i < 2 * vertexN; i++) {
		startR[i] = sum;
		sum += ind[i];
	}
	for (int u = 0; u < 2 * vertexN; u++) { // H <vertexH edgeH> is the graph after deleting high-degree vertex
		if (outd[u] != 0) {                // HR is H's reverse graph
			for (int e = start[u]; e < (start[u] + outd[u]); e++) {
				int curE = edge[e];
				edgeR[startR[curE]++] = u;
			}
		}
	}
	sum = 0;
	for (int i = 0; i < 2 * vertexN; i++) {
		startR[i] = sum;
		sum += ind[i];
	}
}

void findHD()   //remove high degree
{
	//find out the max K out degree
	for (int l = 0; l < K; l++)
		Hdegree[l] = l;   //initialize
	memcpy(indice, outd, sizeof(int) * vertexN);
	int minIndex = 0;
	for (int j = 0; j < K; j++) {
		if (indice[j] < indice[minIndex])
			minIndex = j;
	}
	for (int i = K; i < vertexN; i++) {
		if (outd[i] > indice[minIndex]) {
			indice[minIndex] = outd[i];
			Hdegree[minIndex] = i;
			for (int j = 0; j < K; j++) {
				if (indice[j] < indice[minIndex])
					minIndex = j;
			}
		}
	}

}

void removeHD() {
    for(int l=0; l<K; l++){
	for (int i = 0; i < vertexN; i++) {
		if (i == Hdegree[l]) {
			for (int j = start[i]; j < (start[i] + outd[i]); j++) {
				ind[edge[j]]--;
			}
		} else {
			for (int j = start[i]; j < (start[i] + outd[i]); j++) {
				if (edge[j] == Hdegree[l]) {
					edge[j] = edge[start[i] + outd[i] - 1];
					outd[i]--;
					break;
				}
			}
                sort(edge+start[i],edge+start[i]+outd[i]);
		}
	}
	ind[Hdegree[l]] = outd[Hdegree[l]] = 0;
  }
}


void DAG() {
	int curV, curE, dagN = 0, dagV, dagE;
	memset(dag, -1, sizeof(int) * vertexN);
	memset(indice, -1, sizeof(int) * vertexN);
	for (int us = 0; us < vertexN; us++) {
		if (indice[us] == -1) {  // not be accessed
			dS.push(us);
			dagV = 0;
			dagE = 0;
			while (!dS.empty()) {
				curV = dS.top();
				dag[curV] = dagN;
				dS.pop();
				if (indice[curV] == -1) {
					indice[curV] = 0;
					dS.push(curV);   //access it's edges
					for (int es = start[curV]; es < (start[curV] + outd[curV]);
							++es) {
						curE = edge[es];
						if (indice[curE] == -1)
							dS.push(curE);
					}

					for (int esr = startR[curV];
							esr < (startR[curV] + ind[curV]); ++esr) {
						curE = edgeR[esr];
						if (indice[curE] == -1)
							dS.push(curE);
					}
				} else {
					if (indice[curV] == 0) {  // it's neighbor has been accessed
						indice[curV] = 1;
						dagV++;
						dagE += outd[curV];
					}
				}
			}
			dagN++;
		}
	}//write DAG
	tgraph2 =pt2;
	char dag_l[20]="_dag_label";
	for(char *i=dag_l; *i != '\0'; i++){
		label_name[tgraph2++]=*i;
	}
	label_name[tgraph2]='\0';
	FILE *bfile = fopen(label_name,"wb+");
	fwrite(dag,SZ_VERTEX,vertexN,bfile);
	fclose(bfile);
	free(dag);
}

void topoSort_B() {  //original graph's topological level
	int head = 0, tail = 0;
	int* Q_B = (int *) malloc(sizeof(int) * (vertexN));
	int* topo = (int *) malloc(sizeof(int) * (vertexN));
	memcpy(indice, ind, sizeof(int) * vertexN);
	for (int i = 0; i < vertexN; ++i)
		if ((indice[i] == 0) & (outd[i] != 0))
			Q_B[tail++] = i;
	int mark = tail;
	level = 1;
	while (head < tail) {
		if (head == mark) {
			mark = tail; // (tail-head) vertices at this level
			++level;
		}
		topo[Q_B[head]] = level, topo[Q_B[head]] = level;
		int s = Q_B[head++];
		for (int j = start[s]; j < (start[s] + outd[s]); ++j) {
			int t = edge[j];
			if ((--indice[t]) == 0)
				Q_B[tail++] = t;
		}
	} // how may vertex in Q
	cout<<level<<" original topological level"<<endl;
	tgraph2 =pt2;
	char dag_l[20]="_topo_label";
	for(char *i=dag_l; *i != '\0'; i++){
		label_name[tgraph2++]=*i;
	}
	label_name[tgraph2]='\0';
	FILE * bfile1 = fopen(label_name, "wb+");
	fwrite(topo,SZ_VERTEX,vertexN,bfile1);
	fclose(bfile1);
	free(Q_B);
	free(topo);
}

int topoSort() {  //after deleting high degree vertices
	int head = 0, tail = 0;
	Q = (int *) malloc(sizeof(int) * (2 * vertexN));
	L = (int *) malloc(sizeof(int) * (2 * vertexN));
	memcpy(indice, ind, sizeof(int) * vertexN);
	for (int i = 0; i < vertexN; ++i)
		if ((indice[i] == 0) & (outd[i] != 0)){
			Q[tail++] = i;
		}
	int mark = tail;
	level = 1;
	while (head < tail) {
		if (head == mark) {
			mark = tail; // (tail-head) vertices at this level
			++level;
		}
		L[Q[head]] = level;
		int s = Q[head++];
		for (int j = start[s]; j < (start[s] + outd[s]); ++j) {
			int t = edge[j];
			if ((--indice[t]) == 0){
				Q[tail++] = t;
			}
		}
	}
	return tail;   // how may vertex in Q
}

void PreInerconect(int Qnum) //Qnum is the remaining vertex number after some rounds of interconnection
{ // Qnum is the length of Q(store vertices from low level to bigger level)
	memset(ficout, 0, sizeof(bool) * 2 * vertexN);
	memset(ficin, 0, sizeof(bool) * 2 * vertexN);
	int l = 1, head = 0;
	int number = 0, beE = 0, crossE = 0, min = (vertexN - K), max = 0;

	while (head < Qnum) {
		if (L[Q[head]] == l) {   //from the first level, namely from Q[0]
			number++;
			int s = Q[head++];
			if (outd[s] > max)
				max = outd[s];
			if (outd[s] < min)
				min = outd[s];
			for (int j = start[s]; j < (start[s] + outd[s]); ++j) {
				int t = edge[j];
				if (L[t] == (l + 1))
					beE++;
				else {         //cross edge
					crossE++;
					//fictitious vertex is added in the following four situation
					if (((L[t] - l) > 2) & (L[t] % 2 == 1) & (l % 2 == 1)) //both vertex are in even level and the difference is more than 2
						ficout[s] = ficin[t] = 1;
					else {
						if (((L[t] - l) == 2) & (L[t] % 2 == 1)) //both vertex are in even level and the difference equals to 2
							ficout[s] = 1;
						else {
							if ((l % 2 == 0) & (L[t] % 2 == 1)) //the start vertex is in odd level while the end vertex is in even level
								ficin[t] = 1;
							else {
								if ((l % 2 == 1) & (L[t] % 2 == 0)) //the start vertex is in even level while the end vertex is in odd level
									ficout[s] = 1;
							}
						}
					}
					// }
				}
			}
		} else {
			l++;
			number = 0;
			beE = 0;
			crossE = 0;
			min = (vertexN - K);
			max = 0;
		}
	}
}


int interconnect(int numb, FILE *pf, int nround) //numb is the length of queue(store the remaining vertex in ascending of level )
{
	int * indexG = (int *) malloc(sizeof(int) * 2 * vertexN);
	for (int i = 0; i < 2 * vertexN; i++)
		indexG[i] = -1;               //initialization
	int cur = 0, qne = 0, j = 0,  countin = 0, countout = 0;

	for (int i = 0; i < numb; i++) {
		int t = Q[i];       //the first vertex in queue
		if ((ind[t] != 0) || (outd[t] != 0)) {
			if (L[t] % 2 == 0) {   //if the vertex is in even level
				Lnew[t] = L[t] / 2; //then in next round the vertex will be in level=L[t]/2+1
				Qnew[qne++] = t;  //the new queue will store this vertex
				indexG[t] = cur; //inverse function to indicate vertex t is in which position(cur) of the queue
				cur++;
			} else {
				if (i > j) {    //when it is in odd level              
					j = i;
					while ((L[Q[j]] % 2 == 1) & (j < numb)) {
						if (ficin[Q[j]] == 1){
							Qnew[qne++] = Q[j] % vertexN + vertexN;
							indexG[Q[j] % vertexN + vertexN] = cur, cur++, Lnew[Q[j] % vertexN+ vertexN] = L[Q[j]] / 2;
						}
						j++;
					}
				}
				if (ficout[t] == 1)
					indexG[t] = cur, cur++, Lnew[t] = (L[t] + 1) / 2, Qnew[qne++] =t;
			}
		}
	}
        vector<int> * newG = new vector<int> [cur];
	for (int j = 0; j < numb; j++) {
		int curV = Q[j];  //actually Q and indexG are two reverse function
		int cVnew = indexG[curV]; //the position (j) of vertex Q[j]?
		if (((ind[curV] != 0) || (outd[curV] != 0))) {
			if ((L[curV] % 2 == 0)) {  //if start vertex is in odd level
				for (int e = start[curV]; e < (start[curV] + outd[curV]); ++e) {
					int curE = edge[e];  //end vertex
					if (L[curE] % 2 == 0)  //if end vertex is in odd level
						newG[cVnew].push_back(curE); //then just add this edge to vertex Q[j]

					if ((L[curE] % 2 == 1) && (L[curE] != (L[curV] + 1))) //the edge is in even level but not neighbor
						newG[cVnew].push_back(curE % vertexN + vertexN); //then add it
				}
			} else {  //if start vertex is in even level
				deleV[nround].push_back(curV); // in nth round, vertex t is the curDVth vertex that is deleted
				startSLin[nround].push_back(countin);
				startSLout[nround].push_back(countout);
				if (curV < vertexN) {
					if (R[curV] == -1)
						R[curV] = nround;   //vertex curV is deleted in nround
				}
				vector<int> forward;
				vector<int> reverse;
				//if this start vertex should have a fictitious vertex
				if (ficin[curV] == 1) {
					reverse.push_back(curV % vertexN + vertexN);
					SLin[nround].push_back(curV % vertexN + vertexN), countin++; //SL in label record itself(in)
				}

				for (int rev = startR[curV]; rev < (startR[curV] + ind[curV]);++rev) {
					int curE = edgeR[rev];  //look back to its neighbor
					if ((L[curE] == L[curV] - 1) | (L[curE] == L[curV] - 2)) //if the end vertex is in neighbor level then store in "reverse"
							{
						reverse.push_back(curE);
						SLin[nround].push_back(curE), countin++; //SL in label record its in neighbors and 2(considering 2-4)
					}
				}
				 //store in the "forward"
				if (ficout[curV] == 1)  {
					forward.push_back(curV);
					SLout[nround].push_back(curV), countout++; //SL out label
				}
				for (int forw = start[curV]; forw < (start[curV] + outd[curV]);++forw) {
					int curE = edge[forw];
					//in neighbor level then store in "forward"
					if ((L[curE] == L[curV] + 1)) {
						forward.push_back(curE);
						SLout[nround].push_back(curE), countout++;
					} else {
						if (((L[curE] - L[curV]) > 2) & (L[curE] % 2 == 1)) //both in even level and difference is more than 2
							newG[cVnew].push_back(curE % vertexN + vertexN); // then store it as an edge of vertex Q[j]
						if (L[curE] % 2 == 0) // if the end vertex is in odd level then just store it
							newG[cVnew].push_back(curE);
					}
				}
				//join the neighbor two odd level
				for (unsigned int r = 0; r < reverse.size(); r++) {
					int joinV = reverse[r];
					int joinVnew = indexG[joinV];
					for (unsigned int f = 0; f < forward.size(); f++) {
						int joinE = forward[f];
						newG[joinVnew].push_back(joinE); //join  except (u-v=ns)  two ficticious of the same vertex
					}
				}
			}   //even level
		} else {   //if it has no in neighbor nor out-neighbor
			deleV[nround].push_back(curV); // in nth round, vertex t is the curDVth vertex that is deleted
			startSLin[nround].push_back(countin);
			startSLout[nround].push_back(countout);
			if (curV < vertexN) {
				if (R[curV] == -1)
					R[curV] = nround;
			}
		}
	}
	startSLin[nround].push_back(countin);
	startSLout[nround].push_back(countout);
        int edgeNumber = 0;
        vector<int>::iterator it;
	for (int i = 0; i < 2 * vertexN; i++) {
	        int curV = indexG[i];
	        if ((indexG[i] != -1) & (newG[curV].size() != 0)){
	            sort(newG[curV].begin(), newG[curV].end());
	            it = unique(newG[curV].begin(), newG[curV].end());
	            newG[curV].erase(it, newG[curV].end());
	            edgeNumber+=newG[curV].size();
	        }

	}
	fprintf(pf, "%d %d\n", vertexN, edgeNumber);
	for (int i = 0; i < 2 * vertexN; i++) {  //write this graph in a file
		int curV = indexG[i];
		if ((indexG[i] != -1) & (newG[curV].size() != 0)) {
			fprintf(pf, "%d %d", i, (int) newG[curV].size());
			for (unsigned int j = 0; j < newG[curV].size(); j++)
				fprintf(pf, " %d", newG[curV][j]);
			fprintf(pf, "\n");
		}
	}
	printf("%d vertex deleted\n",(int) deleV[nround].size());
	/*printf("%d total TLin(non-track back) size,", (int) SLin[nround].size());
	printf("%d total TLout(non-track back) size\n", (int) SLout[nround].size());*/
	free(indexG);
	for (int i = 0; i < cur; i++)
		newG[i].clear();
	delete[] newG;
	return cur;
}



void Hdfs() {
	int numHin = 0, numHout = 0;
	stack<int> dfsT;
	int i = Hdegree[0];

	memset(indice, -1, sizeof(int) * vertexN);
	dfsT.push(i);

	while (!dfsT.empty())  //DFS visit
	{
		int curVtest = dfsT.top();
		dfsT.pop();
		if (curVtest != i) {
			numHout++;
			outH.push_back(curVtest);
		}
		for (int e = start[curVtest]; e < start[curVtest] + outd[curVtest];
				e++) {
			if (indice[edge[e]] == -1) {
				dfsT.push(edge[e]);
				indice[edge[e]] = 0;
			}
		}
	}
	reverse();
	memset(indice, -1, sizeof(int) * vertexN);
	dfsT.push(i);

	while (!dfsT.empty())  //DFS visit
	{
		int curVtest = dfsT.top();
		dfsT.pop();
		if (curVtest != i) {
			numHin++;
			inH.push_back(curVtest);
		}
		for (int e = startR[curVtest]; e < startR[curVtest] + ind[curVtest];
				e++) {
			if (indice[edgeR[e]] == -1) {
				dfsT.push(edgeR[e]);
				indice[edgeR[e]] = 0;
			}
		}
	}
}



void creatM() {
	start = (int *) malloc(sizeof(int) * (vertexN) * 2);
	edge = (int *) malloc(sizeof(int) * (edgeN));
	outd = (int *) malloc(sizeof(int) * (vertexN) * 2);
	ind = (int *) malloc(sizeof(int) * (vertexN) * 2);
	dag = (int *) malloc(sizeof(int) * (vertexN));
	indice = (int *) malloc(sizeof(int) * (vertexN) * 2);
	startR = (int *) malloc(sizeof(int) * (vertexN) * 2);
	edgeR = (int *) malloc(sizeof(int) * (edgeN));
}

void load(FILE *infile){
		int ret=fscanf(infile, "%d%d", &vertexN, &edgeN);
		int m = 0, u, deg;
		creatM();
		memset(ind, 0, sizeof(int) * vertexN);
		start[0] = 0;
		while (fscanf(infile, "%d%d", &u, &deg) == 2) {
			start[u] = m;
			outd[u] = deg;
			for (int j = 0; j < deg; ++j) {
				int v;
				int ret=fscanf(infile, "%d", &v);
				ind[v]++;
				edge[m++] = v;
			}
			if (m >= edgeN)
				break;
		}

		cout << vertexN << "total vertex in DAG," << edgeN << "total edges in DAG" << endl;
		start[vertexN] = m;
		for (int i = vertexN - 1; i > 0; --i)  //i>u?
			if ((outd[i] == 0) & (start[i] == 0))  //change
				start[i] = start[i + 1];
		fclose(infile);
}

void createTFH(){
	R = (int *) malloc(sizeof(int) * vertexN); //vertex i is delete in which round
	ficout = (bool *) malloc(sizeof(bool) * (2 * vertexN));
	ficin = (bool *) malloc(sizeof(bool) * (2 * vertexN));
	Lnew = (int *) malloc(sizeof(int) * (2 * vertexN));
	Qnew = (int *) malloc(sizeof(int) * (2 * vertexN));
}

void TFHierachy(){
	createTFH();
	int Qnumber = topoSort();   //  Qnumber is the number of queue
	printf("%dtotal DAG levels after deleting high-degree vertices\n", level);
	reverse();
	round=0;
	printf("++++++++++++++++++TF Hierrarchy++++++++++++++\n");
	int r_level = level, nr = 0;//nr is the round's number
	long fn = 1;
	while (r_level > 1) {
		round++;
		r_level = r_level / 2;
	}
	printf("%d total round in TF hierarchy \n", round);   //we need to do round "round"
	memset(R, -1, sizeof(int) * vertexN);
	while (level > 1) {
		printf("\n%d th round  \n", nr+1);
		PreInerconect(Qnumber);
		tgraph =pt;
		for (long i=fn; i!=0; i=i/10){
			s[tgraph++]=(char)i%10+'0';
		}
		s[tgraph]='\0';
		FILE *graph = fopen(s,"w+");
		fpos_t position;
		fgetpos(graph, &position);  //the biginning position
		if(graph==NULL){
				printf ("Error opening file");
		}
		int QnumNew = interconnect(Qnumber, graph, nr); //nr is the round's number
		nr++;
		int Mnew = 0,u,deg;
		memset(start, -1, sizeof(int) * 2 * vertexN);
		memset(outd, 0, sizeof(int) * 2 * vertexN);
		memset(ind, 0, sizeof(int) * 2 * vertexN);
		free(edge);
		free(edgeR);

		fsetpos(graph, &position);   //read from the begining
		int ret=fscanf(graph, "%d%d", &vertexN, &edgeN);
		edge = (int *) malloc(sizeof(int) * (edgeN));
		edgeR = (int *) malloc(sizeof(int) * (edgeN));
		while (fscanf(graph, "%d%d", &u, &deg) == 2) { //u is vertex and deg is degree
			start[u] = Mnew;
			outd[u] = deg;
			for (int j = 0; j < deg; ++j) {
				int v;
				int ret=fscanf(graph, "%d", &v);
				edge[Mnew++] = v;
				ind[v]++;
			}
		}
		fclose(graph);
		if(remove(s)!=0) printf ("Error deleting file");
		level = (level) / 2;
		printf("after %d's round, %d vertex,%d edge,%d LEVEL \n",nr,QnumNew,edgeN,level);
		for (int i = 0; i < 2 * vertexN; i++) {
			L[i] = Lnew[i];
			Q[i] = Qnew[i];
		}
		reverse();
		fn++;
		Qnumber = QnumNew;
	}
}
void update_round(int *copy, vector<int>last){
	if(last.size()>0){
		copy=(int *)malloc((last.size()+1)*sizeof(int ));
		copy[0]=last.size();
		for(int i=1;i<=copy[0];i++)
			copy[i]=last[i];
	}
	else{
		copy=(int *)malloc(1*sizeof(int ));
		copy[0]=0;
	}
}

void labelConstruction(){
        int TLin_N=0,TLout_N=0;
	SL = new vector<int> [2 * vertexN];
	vector<int> * SLtmp = new vector<int> [2 * vertexN];
        int *TLout_start=(int *)malloc( (2 * vertexN+1)*sizeof(int));
   	int *TLin_start=(int *)malloc( (2 * vertexN+1)*sizeof(int));
    	int *TLout=(int *)malloc( 1*sizeof(int));
    	int *TLin=(int *)malloc( 1*sizeof(int));
    	for(int i=0;i<2 * vertexN;i++){
    		TLout_start[i]=TLin_start[i]=0;
    	}  //initialization
    	TLout_start[2 * vertexN]=TLin_start[2 * vertexN]=0;

	for(int r=round-1; r>=0;r--){
		printf("%d round begin",r+1);

		for(int i=0; i<rN[r];i++){
			int curVr=deleV1[r][i];
			if((curVr < vertexN) & (R[curVr % vertexN] == r)){
				if(SLtmp[curVr].size()>0){  //capacity?
					vector<int> b;
					SLtmp[curVr].swap(b);
				}
				if(SLtmp[curVr+vertexN].size()>0){  //capacity?
					vector<int> b;
					SLtmp[curVr+vertexN].swap(b);
				}
				//out label
				for (int j = startSLout1[r][i]; j < startSLout1[r][i + 1]; j++) {  //original out label
					int curEr = SLout1[r][j]; // curEr is its neighbor in r+1 th G
					//three cases
					if (SLout1[r][j] != curVr) { //if its fictitious out then we have already do this in last step???
						SL[curVr].push_back(curEr);
						if ((curEr < vertexN) & (R[curEr % vertexN] > r)) { //if it is original vertex
							for (unsigned int k = 0; k < SL[curEr].size(); k++) { // the latest curEr'S ls LABEL
								SL[curVr].push_back(SL[curEr][k]);
							}
						} else {

							if (curEr < vertexN) { //fictitious out
								for ( int k = TLout_start[curEr]; k <TLout_start[curEr+1];k++) { // the latest curEr'S ls LABEL
									SL[curVr].push_back(TLout[k]);
								}
							} else {  //fictious in vertex
								for (int k = TLin_start[curEr-vertexN];k<TLin_start[curEr-vertexN+1];k++) {
									SL[curVr].push_back(TLin[k]);
								}
							}
						}
					}
				}
			    //in label
				for (int j = startSLin1[r][i]; j < startSLin1[r][i + 1]; j++) {  //in label
					int curEr = SLin1[r][j];
					if (curEr != (curVr + vertexN)) {
						SL[curVr + vertexN].push_back(curEr);
						if ((curEr < vertexN) & (R[curEr % vertexN] > r)) { //if it is original vertex
							for (unsigned int k = 0;k < SL[curEr + vertexN].size(); k++) { // the latest curEr'S ls LABEL
								SL[curVr + vertexN].push_back(SL[curEr + vertexN][k]);
							}
						} else {
							if (curEr < vertexN) { //fictitious out
								for (int k =  TLout_start[curEr + vertexN];k <TLout_start[curEr + vertexN+1];k++) { // the latest curEr'S ls LABEL
									SL[curVr + vertexN].push_back(TLout[k]);
							}
						} else {  //fictious in vertex
								for (int k = TLin_start[curEr]; k <TLin_start[curEr+1];k++) {
									SL[curVr + vertexN].push_back(TLin[k]);
								}
							}
						}
					}
				}
				for (int j = 0; j < SL[curVr].size(); j++) {
					if (SL[curVr][j] >= vertexN)
						SL[curVr][j] -= vertexN;
				}
				for (int j = 0; j < SL[curVr+vertexN].size(); j++) {
					if (SL[curVr+vertexN][j] >= vertexN)
						SL[curVr+vertexN][j] -= vertexN;
				}
				vector<int>::iterator it;
				if (SL[curVr].size() > 1) {
					sort(SL[curVr].begin(), SL[curVr].end());
					it = unique(SL[curVr].begin(), SL[curVr].end());
					SL[curVr].erase(it, SL[curVr].end());
				}
				if (SL[curVr+vertexN].size() > 1) {
					sort(SL[curVr+vertexN].begin(), SL[curVr+vertexN].end());
					it = unique(SL[curVr+vertexN].begin(), SL[curVr+vertexN].end());
					SL[curVr+vertexN].erase(it, SL[curVr+vertexN].end());
				}
			}
			else {  //fictious out
				if (curVr < vertexN) { //the deleted vertex is fictitious out vertex
					{vector<int> a;
			                SLtmp[curVr].swap(a);
			                }
					SLtmp[curVr].clear();						// out-fictitious vertex's in label
					for (int j = startSLin1[r][i]; j < startSLin1[r][i + 1]; j++) {
						SLtmp[curVr].push_back(SLin1[r][j]);	// its edge can't have fictitious out or in vertex
						int curEr = SLin1[r][j];
						if ((curEr < vertexN) & (R[curEr % vertexN] > r)) { //if it is original vertex
							for (unsigned int k = 0; k < SL[curEr + vertexN].size();k++) { // the latest curEr'S ls LABEL
								SLtmp[curVr].push_back(SL[curEr + vertexN][k]);
							}
						} else {
							if (curEr < vertexN) { //fictitious out
								for (int k = TLout_start[curEr + vertexN];k<TLout_start[curEr + vertexN+1];k++) { // the latest curEr'S ls LABEL
									SLtmp[curVr].push_back(TLout[k]);
								}
							} else {  //fictious in vertex
								for (int k = TLin_start[curEr];k < TLin_start[curEr+1];k++) {
									SLtmp[curVr].push_back(TLin[k]);
								}
							}
						}
					}
					for (int j = 0; j < SLtmp[curVr].size(); j++) {
					if (SLtmp[curVr][j] >= vertexN)
						SLtmp[curVr][j] -= vertexN;
					}
					vector<int>::iterator it;
					if (SLtmp[curVr].size() > 1) {
						sort(SLtmp[curVr].begin(), SLtmp[curVr].end());
						it = unique(SLtmp[curVr].begin(), SLtmp[curVr].end());
						SLtmp[curVr].erase(it, SLtmp[curVr].end());
					}
					// out label
					for (int j = startSLout1[r][i];j < startSLout1[r][i + 1]; j++) { //out label
						int curEr = SLout1[r][j]; // curEr is its neighbor in r+1 th G
						if (curEr != curVr) { //if its fictitious out then we have already do this in last step???
							SL[curVr].push_back(curEr);
							if ((curEr < vertexN)& (R[curEr % vertexN] > r)) { //if it is original vertex
								for (unsigned int k = 0;k < SL[curEr].size(); k++) { // the latest curEr'S ls LABEL
									SL[curVr].push_back(SL[curEr][k]);
								}
							} else {
								if (curEr < vertexN) { //fictitious out
									for (int k = TLout_start[curEr];k <TLout_start[curEr+1];k++) { // the latest curEr'S ls LABEL
										SL[curVr].push_back(TLout[k]);
									}
								} else {  //fictious in vertex
									for (int k = TLin_start[curEr- vertexN];k<TLin_start[curEr- vertexN+1];k++) {
										SL[curVr].push_back(TLin[k]);
									}
								}
							}
						}
					}
					for (int j = 0; j < SL[curVr].size(); j++) {
					if (SL[curVr][j] >= vertexN)
						SL[curVr][j] -= vertexN;
					}
					
					if (SL[curVr].size() > 1) {
						sort(SL[curVr].begin(), SL[curVr].end());
						it = unique(SL[curVr].begin(), SL[curVr].end());
						SL[curVr].erase(it, SL[curVr].end());
					}
				}
				else {
					{vector<int> a;
			                SLtmp[curVr].swap(a);
			                }
					SLtmp[curVr].clear();
					for (int j = startSLout1[r][i]; j < startSLout1[r][i + 1]; j++) {
						SLtmp[curVr].push_back(SLout1[r][j]);// its edge can't have fictitious out or in vertex
						int curEr = SLout1[r][j];
						if ((curEr < vertexN) & (R[curEr % vertexN] > r)) { //if it is original vertex
							for (unsigned int k = 0; k < SL[curEr].size(); k++) { // the latest curEr'S ls LABEL
								//change 2
								SLtmp[curVr].push_back(SL[curEr][k]); //in-fictitious vertex's out neighbor
							}
						} else {
							if (curEr < vertexN) { //fictitious out
								for ( int k = TLout_start[curEr];k <TLout_start[curEr+1];k++) { // the latest curEr'S ls LABEL
									SLtmp[curVr].push_back(TLout[k]);
								}
							} else {  //fictious in vertex
								for (int k = TLin_start[curEr- vertexN];k<TLin_start[curEr- vertexN+1];k++) {
									SLtmp[curVr].push_back(TLin[k]);
								}
							}
						}
					}

					for (int j = 0; j < SLtmp[curVr].size(); j++) {
					if (SLtmp[curVr][j] >= vertexN)
						SLtmp[curVr][j] -= vertexN;
					}
					vector<int>::iterator it;
					if (SLtmp[curVr].size() > 1) {
						sort(SLtmp[curVr].begin(), SLtmp[curVr].end());
						it = unique(SLtmp[curVr].begin(), SLtmp[curVr].end());
						SLtmp[curVr].erase(it, SLtmp[curVr].end());
					}
					for (int j = startSLin1[r][i];j < startSLin1[r][i + 1]; j++) {  //in label
						int curEr = SLin1[r][j];
						if (curEr != curVr) {
							SL[curVr].push_back(curEr);
							if ((curEr < vertexN) & (R[curEr % vertexN] > r)) { //if it is original vertex
								for (unsigned int k = 0;k < SL[curEr + vertexN].size();k++) { // the latest curEr'S ls LABEL
									SL[curVr].push_back(SL[curEr + vertexN][k]);
								}
							} else {
								if (curEr < vertexN) { //fictitious out
									for ( int k = TLout_start[curEr+ vertexN];k<TLout_start[curEr+ vertexN+1];k++) { // the latest curEr'S ls LABEL
										SL[curVr].push_back(TLout[k]);
									}
								} else {  //fictious in vertex
									for ( int k =  TLin_start[curEr];k < TLin_start[curEr+1];k++) {
										SL[curVr].push_back(TLin[k]);
									}
								}
							}
				            }
			             }
			             for (int j = 0; j < SL[curVr].size(); j++) {
					if (SL[curVr][j] >= vertexN)
						SL[curVr][j] -= vertexN;
					}
					
					if (SL[curVr].size() > 1) {
						sort(SL[curVr].begin(), SL[curVr].end());
						it = unique(SL[curVr].begin(), SL[curVr].end());
						SL[curVr].erase(it, SL[curVr].end());
					}
				}
			}
		}
	free(SLin1[r]);
	free(SLout1[r]);
	free(deleV1[r]);	
	free(startSLout1[r]);
	free(startSLin1[r]);
        free(TLout);
        free(TLin);
        if(r==0) {
        	printf("   1 round end\n"); 
        	break;}
        TLout_N=TLin_N=0;
        for(int k=0;k<vertexN;k++){
        	if(R[k] < r){
        		TLout_N+=SL[k].size();
        		TLout_N+=SLtmp[k].size();
        		TLin_N+=SLtmp[k+vertexN].size();
        		TLin_N+=SL[k+vertexN].size();
        	}
        }
        TLin=(int *)malloc((TLin_N)*sizeof(int ));
        TLout=(int *)malloc((TLout_N)*sizeof(int ));
        TLout_start[0]=TLin_start[0]=0;
        for(int k=0;k<2*vertexN;k++){
        	if(R[k%vertexN] < r){
        		if(k<vertexN){
        		    TLout_start[k+1]=TLout_start[k]+SL[k].size();
        		    for(int l=TLout_start[k];l<TLout_start[k+1];l++){
        		    	TLout[l]=SL[k][l-TLout_start[k]];
        		    }
        		    TLin_start[k+1]=TLin_start[k]+SLtmp[k+vertexN].size();
        		    for(int l=TLin_start[k];l<TLin_start[k+1];l++){
        		    	TLin[l]=SLtmp[k+vertexN][l-TLin_start[k]];
        		    }
        		}
        		else{
        			TLout_start[k+1]=TLout_start[k]+SLtmp[k-vertexN].size();
        			for(int l=TLout_start[k];l<TLout_start[k+1];l++){
						TLout[l]=SLtmp[k-vertexN][l-TLout_start[k]];
					}
        		    TLin_start[k+1]=TLin_start[k]+SL[k].size();
        		    for(int l=TLin_start[k];l<TLin_start[k+1];l++){
        		    	TLin[l]=SL[k][l-TLin_start[k]];
        		    }
        		}
        	}
        	else{
        		TLout_start[k+1]=TLout_start[k];
        		TLin_start[k+1]=TLin_start[k];
        	}

        }
        printf("   %d round end\n",r+1);
	}
	free(R);
	free(SLin1);
	free(SLout1);
	free(deleV1);	
	free(startSLout1);
	free(startSLin1);
	free(TLout_start);
        free(TLin_start);
	delete[] SLtmp;
}
void TLabel(){
	for (int i = 0; i < inH.size(); i++){
		SL[inH[i]].push_back(Hdegree[0]);
	}

	for (int i = 0; i < outH.size(); i++){
		SL[outH[i] + vertexN].push_back(Hdegree[0]);
	}
	long numSL = 0;
	vector<int>::iterator it;
	for (int i = 0; i < 2 * vertexN; i++) {
		numSL = numSL + SL[i].size();
		/*if(i==(vertexN-1))
			cout << numSL << " Total out TLable"<<endl;*/
     		SL[i].push_back(i%vertexN);   //include itself
		if (SL[i].size() > 1) {
			sort(SL[i].begin(), SL[i].end());
		}
	}
	rt.stop();
	cout << numSL << " Total TLable;" << numSL / vertexN << " Average TL" << endl;
	tgraph2 =pt2;
	char tl_l[20]="_TL";
	for(char *i=tl_l; *i != '\0'; i++){
		label_name[tgraph2++]=*i;
	}
	label_name[tgraph2]='\0';
	FILE * bfile2 = fopen(label_name, "wb+");
	vertex_id * write_buff = (vertex_id *) malloc(BLK_SZ);
	int ptr_buff = 0;
	for(int i=0; i<2*vertexN; i++){
		for(int j=0; j<SL[i].size(); j++){
			write_buff[ptr_buff++]=SL[i][j];  //arrSL[i][j];
			if(ptr_buff == VERTEX_PER_BLK){
				fwrite(write_buff,SZ_VERTEX,ptr_buff,bfile2);
				ptr_buff = 0;
			}
		}
	}
	if(ptr_buff>0){
		fwrite(write_buff,SZ_VERTEX,ptr_buff,bfile2);
		ptr_buff = 0;
	}
	fclose(bfile2);
	tgraph2 =pt2;
	char dag_l[20]="_tlstart";
	for(char *i=dag_l; *i != '\0'; i++){
		label_name[tgraph2++]=*i;
	}
	label_name[tgraph2]='\0';
	FILE * bfile3 = fopen(label_name, "wb+");
	for(int i=0; i<2*vertexN; i++){
		write_buff[ptr_buff++]=SL[i].size();  //arrSL[i][j];
		if(ptr_buff == VERTEX_PER_BLK){
			fwrite(write_buff,SZ_VERTEX,ptr_buff,bfile3);
			ptr_buff = 0;
		}

	
	}
	if(ptr_buff>0){
		fwrite(write_buff,SZ_VERTEX,ptr_buff,bfile3);
		ptr_buff = 0;
	}
    	fclose(bfile3);
}

void delet(){

	free(edge);
	free(start);
	free(startR);
	free(edgeR);
	free(ind);
	free(outd);
	free(indice);
        free(Q);
        free(L);
        free(Qnew);
        free(Lnew);
        free(ficout);
        free(ficin);

}

void transform(){
	 vector<int> a1[round],a2[round],a3[round],a4[round],a5[round];
	 for(int i=0;i<round;i++)
	 {
		 rN[i]=deleV[i].size();
	 }
	 SLin1=(int **)malloc( round*sizeof(int *));
	 for(int i=0;i<round;i++){
		 SLin1[i]=(int *)malloc(SLin[i].size()*sizeof(int ));
		 for(int j=0;j<SLin[i].size();j++)
			 SLin1[i][j]=SLin[i][j];
	 }
	 for(int i=0;i<round;i++){
		 SLin[i].swap(a1[i]);
	 }
	 SLout1=(int **)malloc( round*sizeof(int *));
	 for(int i=0;i<round;i++){
		 SLout1[i]=(int *)malloc(SLout[i].size()*sizeof(int ));
		 for(int j=0;j<SLout[i].size();j++)
			 SLout1[i][j]=SLout[i][j];
	 }
	 for(int i=0;i<round;i++){
		 SLout[i].swap(a2[i]);
	 }
	 deleV1=(int **)malloc( round*sizeof(int *));
	 for(int i=0;i<round;i++){
		 deleV1[i]=(int *)malloc(deleV[i].size()*sizeof(int ));
		 for(int j=0;j<deleV[i].size();j++)
			 deleV1[i][j]=deleV[i][j];
	 }
	 for(int i=0;i<round;i++){
		 deleV[i].swap(a3[i]);
	 }
	 startSLout1=(int **)malloc( round*sizeof(int *));
	 for(int i=0;i<round;i++){
		 startSLout1[i]=(int *)malloc(startSLout[i].size()*sizeof(int ));
		 for(int j=0;j<startSLout[i].size();j++)
			 startSLout1[i][j]=startSLout[i][j];
	 }
	 for(int i=0;i<round;i++){
		 startSLout[i].swap(a4[i]);
	 }
	 startSLin1=(int **)malloc( round*sizeof(int *));
	 for(int i=0;i<round;i++){
		 startSLin1[i]=(int *)malloc(startSLin[i].size()*sizeof(int ));
		 for(int j=0;j<startSLin[i].size();j++)
			 startSLin1[i][j]=startSLin[i][j];
	 }
	 for(int i=0;i<round;i++){
		 startSLin[i].swap(a5[i]);
	 }
}

int main(int argc, char **argv) {

// read DAG
	if (argc == 1) {
		usage();
		return 1;
	}
	int i = 1;
	char *filename,*resfilename; // *resfilename="../index/"
	while (i < argc) {
		if (strcmp("-h", argv[i]) == 0) {
			usage();
			return 1;
		}
		if (strcmp("-i", argv[i]) == 0) {
			i++;
			resfilename = argv[i++];
		}		
		else {
			filename = argv[i++];
		}			
	}
	FILE *in_file = fopen(filename, "r");
        load(in_file);
	
	rt.start();
	findHD();
	for (int q = 0; q < K; q++)
		printf("%d th highdegree vertex: %d out degree\n", q+1, outd[Hdegree[q]]);
	Hdfs();
	for(char *i=resfilename; *i != '\0'; i++){
			label_name[tgraph2++]=*i;
	}
	pt2=tgraph2;
	DAG();
	topoSort_B();
	printf("++++++++++++Remove highdegree vertices+++++++++++++++++++\n");
	removeHD();
        char tmpf[5]="g";
	for(char *i=tmpf; *i != '\0'; i++){
			s[tgraph++]=*i;
	}
	pt=tgraph;
	

	TFHierachy();
	delet();
	transform();
        printf("++++++++++++Label Construction(top-down)+++++++++++++\n");
	labelConstruction();
	printf("++++++++++++Add high-degree vertices' label++++++++++++++\n");
	TLabel();
	
	printf("Time used: %lf\n",rt.GetRuntime());
	delete[] SL;

	printf("/////////////////////////////////////////////////// \n");
	return 0;
}



