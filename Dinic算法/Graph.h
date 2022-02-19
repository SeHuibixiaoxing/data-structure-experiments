#pragma once

#include <vector>
#include "Edge.h"

class Graph
{
	std::vector<Edge> edge;
	std::vector<int> head;
	std::vector<int> h;
	int n, m;
	int S, T;

	int getAnother(int pos);

	int dfsForFordFulkerson(int x, int mi, std::vector<bool>& vis);

	bool bfs();

	int dfsForDinic(int x, int f);

public:
	Graph(int S, int T, int n);
	void insert(int u, int v, int w = 0);
	int runFordFulkerson();
	int runDinic();
};