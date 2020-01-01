#include <iostream>
using namespace std;
#include<list>
#include<vector>
class Graph {
public:
	int v;
	list<int>* adj;
public:
	Graph(int v);
	void edge(int v, int w);
	void bfs(int s,bool visited[]);
	void dfs(int s,bool visited[],bool recstack[]);
	bool iscyclic(int s, bool visited[], bool recstack[],int n,vector<int>&stc);
	void print(bool recstack[],int n,vector<int>&stc);
};
Graph::Graph(int v) {
	this->v = v;
	adj = new list<int>[v];
}
void Graph:: edge(int v, int w) {
	adj[v].push_back(w);
}
void Graph :: bfs(int s,bool visited[]) {
	list<int>::iterator i;
	list<int>q;
	q.push_back(s);
	while (!q.empty()) {
		int n=q.front();
		visited[n] = true;
		q.pop_front();
		for (auto i = adj[n].begin(); i != adj[n].end(); i++) {
			if (visited[*i] == false) {
				visited[*i] = true;
				q.push_back(*i);
			}
		}
	}
}
void Graph::dfs(int s,bool visited[],bool recstack[]) {
	list<int>::iterator i;
	visited[s] = true;
	recstack[s] = true;
	for (auto i = adj[s].begin(); i != adj[s].end(); i++) {
		if (recstack[*i] == true) {
			cout << 1;
			break;
		}
		if (visited[*i] == false) {
			dfs(*i, visited,recstack);
		}
	}
}
void Graph::print(bool recstack[],int n,vector<int>&stc) {
	int s = stc[stc.size() - 1];
	stc.pop_back();
	int i = stc.size() - 1;
	cout << s;
	while(stc[i]!=s) {
		cout << stc[i];
		i--;
	}
	cout << endl;
}
bool Graph::iscyclic(int s, bool visited[], bool recstack[],int n,vector<int>&stc) {
	list<int>::iterator i;
	static int count = 0;
	if (visited[s] == false) {
		visited[s] = true;
		recstack[s] = true;
		stc.push_back(s);
		for (auto i = adj[s].begin(); i != adj[s].end(); i++) {
			if (recstack[*i]) {
				stc.push_back(*i);
				print(recstack,n,stc);
				count++;
			}
			if (!visited[*i])
				iscyclic(*i, visited, recstack, n, stc);
		}
	}
	recstack[s] = false;
	stc.pop_back();
	if (count == 0)
		return false;
	else
		return true;
}
int main()
{
	int n;
	cin >> n;
	int e;
	Graph g(n);
	cin >> e;
	int v1;
	int v2;
	for (int i = 0; i < e; i++) {
		cin >> v1;
		cin >> v2;
		g.edge(v1, v2);
	}
	bool* visited = new bool[n];
	/*for (int i = 0; i < n; i++)
		visited[i] = false;
	g.bfs(s, visited);
	for (int i = 0; i < n; i++) {
		if (visited[i] == false)
			g.bfs(i, visited);
	}
	for (int i = 0; i < n; i++)
		visited[i] = false;
	g.dfs(s, visited);
	for (int i = 0; i < n; i++) {
		if (visited[i] == false)
			g.dfs(i, visited);
	}
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int i = 0; i < n; i++)
			visited[i] = false;
		g.bfs(i, visited);
		for (int i = 0; i < n; i++)
			if (visited[i] == true)
				count++;
		if (count == n)
			cout << i;
	}*/
	bool* recstack = new bool[n];
	for (int i = 0; i < n; i++) {
		visited[i] = false;
		recstack[i] = false;
	}
	int flag = 0;
	vector<int>stc;
	for (int i = 0; i < n; i++) {
		if (g.iscyclic(i, visited, recstack,n,stc)) {
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		cout << 1 << endl;
	else
		cout << 0;
}

