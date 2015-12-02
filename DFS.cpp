#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

//data structure
set<int> V;// set of vertices
map<int, set<int> > A;// A[v] is the set of adjacent vertices of v

map<int, int> p;
map<int, int> d;
map<int, int> f;
map<int, char> color;
int t;

int nbCC;
map<int, int> C;// C[v] is the index of connected component containing v
void readData(char* fn){
	FILE* f = fopen(fn,"r");
	int n,m;
	fscanf(f,"%d%d",&n,&m);
	for(int i = 0; i < n; i++){
		int v;
		fscanf(f,"%d",&v);
		V.insert(v);
	}
	for(int i = 0; i < m;i++){
		int u, v;
		fscanf(f,"%d%d",&u,&v);
		A[u].insert(v);
		A[v].insert(u);
	}
	fclose(f);
	
	// print graph
	set<int>::iterator it;
	for(it = V.begin(); it != V.end(); it++){
		int v = *it;
		cout << "A[" << v << "] = ";
		for(set<int>::iterator itv = A[v].begin(); itv != A[v].end(); itv++){
			cout << *itv << " ";
		}
		cout << endl;
	}
}

void DFSVisit(int u){
	t++;
	d[u] = t;
	color[u] = 'G';
	C[u] = nbCC;
	for(set<int>::iterator it = A[u].begin(); it != A[u].end(); it++){
		int v = *it;
		if(color[v] == 'W'){
			p[v] = u;
			DFSVisit(v);
		}
	}
	t++;
	color[u] = 'B';
	f[u] = t;
}

void DFS(){
	nbCC = 0;
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		color[*it] = 'W';
	}
	
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		int u = *it;
		if(color[u] == 'W'){
			nbCC++;
			DFSVisit(u);
		}
	}
	
	// print results
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		cout << *it << "\t";
	}
	cout << endl;
	
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		int u = *it;
		cout << p[u] << "\t";
	}
	cout << endl;
	
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		int u = *it;
		cout << d[u] << "\t";
	}
	cout << endl;
	
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		int u = *it;
		cout << f[u] << "\t";
	}
	cout << endl;
	
	for(int k = 1; k <= nbCC; k++){
		cout << "CC["<< k << " = ";
		for(set<int>::iterator it = V.begin(); it != V.end(); it++){
			int u = *it;
			if(C[u] == k) cout << u << " ";
		}
		cout << endl;
	}
}
void BFS(int s){
	queue<int> Q;
	color[s] = 'G';
	d[s] = 0;// distance from source to s
	Q.push(s);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		cout << u << " ";
		set<int>::iterator it;
		for(it = A[u].begin(); it != A[u].end(); it++){
			int v = *it;
			if(color[v] == 'W'){
				Q.push(v);
				p[v] = u;
				d[v] = d[u] + 1;
				color[v] = 'G';
			}
		}
	}
}
void BFS(){
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		int v = *it;
		color[v] = 'W';
	}
	
	for(set<int>::iterator it = V.begin(); it != V.end(); it++){
		int v = *it;
		if(color[v] == 'W')
			BFS(v);
	}
}

void findPath(int u, int v){
	for(set<int>::iterator it = V.begin();it != V.end(); it++)
		color[*it] = 'W';
	//DFSVisit(u);
	BFS(u);
	// print path
	if(color[v] == 'W'){
		cout << "No path" << endl;
		return;
	}
	cout << "path from " << u << " to " << v << ": ";
	int x = v;
	stack<int> S;
	while(1){
		S.push(x);
		x = p[x];
		if(x == u){
			S.push(x);
			break;
		}
	}
	while(!S.empty()){
		int x = S.top();
		S.pop();
		cout << x << " ";
	}
	cout << endl;
}

int main(int argc, char** argv){
	readData(argv[1]);
	//DFS();
	//BFS();
	findPath(1,12);
	
}