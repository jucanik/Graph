#include <iostream>
using namespace std;
#include<list>
class Graph {
	int v;
	list<int>* adj;
public:
	Graph(int v);
	void addedge(int v, int w);
	void iscyclic(int v, int parent, int mark[], int par[], int& cyclenumber,int color[],int n);
};
enum color { white, gray, black };
void print(int n, int mark[],int cyclenumber) {
	for (int i = 0; i < n; i++) {
		if (mark[i] == cyclenumber)
			cout << i;
	}
	cout << endl;
}
void Graph::iscyclic(int v, int p, int mark[], int par[], int& cyclenumber,int color[],int n) {
	if (color[v]==black)
		return;
	if (color[v] == gray) {
		cyclenumber++;
		int cur = p;
		mark[cur] = cyclenumber;
		while (cur != v) {
			cur = par[cur];
			mark[cur] = cyclenumber;
		}
		print(n, mark,cyclenumber);
		return;
	}
	par[v]=p;
	color[v] = gray;
	list<int>::iterator it;
	for (auto it = adj[v].begin(); it != adj[v].end();it++) {
		int x = *it;
		if (x == par[v])
			continue;
		iscyclic(x, v, mark, par, cyclenumber, color,n);
	}
	color[v] = black;
}
Graph::Graph(int v) {
	this->v = v;
	adj = new list<int>[v];
}
void Graph::addedge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v);
}
void printcycles(int v, int mark[], int& cyclenumber) {
	list<int>* cycle = new list<int>[cyclenumber];
	for (int i = 0; i < v; i++) {
		cycle[mark[i]].push_back(i);
	}
	for (int i = 1; i <= cyclenumber; i++) {
		for (int x : cycle[i])
			cout << x;
		cout << endl;
	}
}
int main()
{
	int v;
	cin >> v;
	Graph g(v);
	int e;
	cin >> e;
	int v1, v2;
	for (int i = 1; i <= e; i++) {
		cin >> v1;
		cin >> v2;
		g.addedge(v1, v2);
	}
	int* mark = new int[v];
	int* par = new int[v];
	int* color = new int[v];
	for (int i = 0; i < v; i++)
		color[i] = white;
	for (int i = 0; i < v; i++)
		mark[i] = 0;
	int cyclenumber = 0;
	g.iscyclic(0, 0, mark, par, cyclenumber,color,v);
}

