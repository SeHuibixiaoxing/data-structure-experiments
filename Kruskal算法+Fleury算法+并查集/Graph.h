#pragma once

#include <vector>
#include "Edge.h"

class Graph
{
	std::vector<Edge> edge;
	std::vector<int> head;
	int n, m;
	int cnt;

	int getAnother(int pos) {
		if (pos & 1) {
			return pos + 1;
		}
		else {
			return pos - 1;
		}
	}
	
	void getEulerDfs(int x, std::vector<Edge>& ans, std::vector<bool>& vis);



public:
	Graph(int n, int m);
	void insert(int u, int v, int w = 0);
	std::vector<Edge>* getMST();
	std::vector<Edge>* getEuler();
};

