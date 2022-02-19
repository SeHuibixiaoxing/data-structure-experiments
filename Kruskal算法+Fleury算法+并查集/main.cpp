
#define _CRT_SECURE_NO_WARNINGS

//#define MST_MODE
#define EULER_MODE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "Graph.h"
#include "Edge.h"
#include "DisjointSet.h"


int main() {
#ifdef MST_MODE

	int n, m;
	scanf("%d %d", &n, &m);
	Graph g(n, m);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		g.insert(u, v, w);
	}
	std::vector<Edge>* edge = g.getMST();
	int sum = 0;
	if ((*edge).size() < n - 1) {
		printf("orz");
	}
	else {
		for (int i = 0; i < n - 1; ++i) {
			sum += (*edge)[i].w;
		}
		printf("%d", sum);
	}

#endif // MST_MODE

#ifdef EULER_MODE
	int n, m;
	scanf("%d %d", &n, &m);
	Graph g(n, m);
	for (int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		g.insert(u, v);
	}
	std::vector<Edge>* edge = g.getEuler();
	if (edge == nullptr) {
		printf("This graph dont have Euler Loop\n");
	}
	else {
		for (int i = 0; i < (*edge).size() - 1; ++i) {
			printf("(%d, %d)->", (*edge)[i].u, (*edge)[i].v);
		}
		printf("(%d, %d)", (*edge)[(*edge).size() - 1].u, (*edge)[(*edge).size() - 1].v);
	}
	
#endif // EULER_MODE



	return 0;
}


