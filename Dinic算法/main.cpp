#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
	int n, m, s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	Graph g(s, t, n);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		g.insert(u, v, w);
	}
	printf("%d", g.runDinic());
	//printf("%d", g.runFordFulkerson());

	return 0;
}