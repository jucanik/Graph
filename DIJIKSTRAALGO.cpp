// DIJIKSTRAALGO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<vector>
using namespace std;
int mindistance(int dist[], bool sptset[],int v) {
	int min = INT_MAX;
	int minindex;
	for (int i = 0; i < v; i++) {
		if (dist[i] < min && sptset[i]==false) {
			min = dist[i];
			minindex = i;
		}
	}
	return (minindex);
}
void print(int dist[], int v,int src,int parent[]) {
	for (int i = 0; i < v; i++) {
		cout << i << '\t' << dist[i]<<'\t';
		int k = i;
		while (parent[k] != src) {
			cout << k;
			k = parent[k];
		}
		if (i != src)
			cout << k << src << endl;
		else
			cout << src << endl;
	}
}
void dijkstra(int graph[][9], int src,int v,int parent[]) {
	int dist[20];
	bool sptset[20];
	for (int i = 0; i < v; i++) {
		dist[i] = INT_MAX;
		sptset[i] = false;
	}
	dist[src] = 0;
	parent[src] = 0;
	for (int count = 0; count < v; count++) {
		int u = mindistance(dist, sptset,v);
		sptset[u] = true;
		for (int j = 0; j < v; j++) {
			if (!sptset[j] && graph[u][j] && dist[u] != INT_MAX && dist[u] + graph[u][j] < dist[j]) {
				dist[j] = dist[u] + graph[u][j];
				parent[j] = u;
			}
		}
	}
	print(dist,v,src,parent);
}
int main()
{
	int we;
	int parent[10];
	int graph[9][9] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
	dijkstra(graph, 0,9,parent);
	cout << endl;
	for (int i = 0; i < 9; i++) {
		cout << parent[i];
	}
}
