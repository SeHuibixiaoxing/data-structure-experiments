#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <vector>
#include <queue>
#include "Graph.h"


int main() {
	int n, m, s;
	std::cin >> n >> m >> s;
	Graph g;
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		g.insert(u, v, w);
	}
	std::vector<int>* d = g.dijkstra(s);
	for (int i = 1; i <= n; ++i) {
		std::cout << (*d)[i] << " ";
	}
	return 0;
}


 
