#include <iostream>
#include<list>
using namespace std;
class Graph {
	int v;
	list<int>* adj;
public:
	Graph(int v);
	void addedge(int v, int w);
	void unionset(int parent[],int x, int y);
	int find(int parent[], int i);
};
Graph::Graph(int v) {
	this->v = v;
	adj = new list<int>[v];
}
void Graph::addedge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v);
}
int  Graph::find(int parent[], int i) {
	if (parent[i] == -1)
		return i;
	return(find(parent, parent[i]));
}
void Graph::unionset(int parent[], int x, int y) {
	int xset = find(parent, x);
	int yset = find(parent, y);
	if (xset != yset)
		parent[xset] = yset;
}
struct edge {
	int i1;
	int i2;
};
void print(int parent[],int v,int w) {
	while (parent[v] != -1) {
		cout << v;
		v = parent[v];
	}
	while (parent[w] != -1) {
		cout << w;
		w = parent[w];
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
	int* parent = new int[v];
	for (int i = 0; i < v; i++)
		parent[i] = -1;
	struct edge* ne = new struct edge[e];
	for (int i = 0; i < e; i++) {
		cin >> v1;
		cin >> v2;
		g.addedge(v1, v2);
		ne[i].i1 = v1;
		ne[i].i2 = v2;
	}
	int flag = 0;
	for (int i = 0; i < e; i++) {
		int z;
		int x = g.find(parent, ne[i].i1);
		int y = g.find(parent, ne[i].i2);
		if ((x != y) && ((parent[ne[i].i1] != -1) || (parent[ne[i].i2] != -1))) {
			if (parent[ne[i].i1] != -1) {
				z = ne[i].i1;
				parent[x] = z;
				parent[ne[i].i1] = ne[i].i2;
			}
			else {
				z = ne[i].i2;
				parent[y] = z;
				parent[ne[i].i2] = ne[i].i1;
			}
		}
		if (x == y) {
			print(parent,ne[i].i1,ne[i].i2); 
			cout << x;
			cout << endl;
			flag = 1;
		}
		g.unionset(parent, x, y);
	}
	if (flag == 1)
		cout << 1;
	else
		cout << 0;
}
