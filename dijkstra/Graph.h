#pragma once 

#include <vector>
#include <queue>

const int INF = 1e9 + 5;

struct Edge {
	int u, v, w, next;
	Edge(const int& u, const int& v, const int& w, const int& next) : u(u), v(v), w(w), next(next) {}
};

class Graph
{	
	std::vector<int> head;
	std::vector<Edge> edge;

	struct Node {
		int v, w;
		Node(const int& v, const int& w) : v(v), w(w) {}
	};

	struct cmp {
		bool operator()(const Node& a, const Node& b) {
			return a.w > b.w;
		}
	};

public:
	void insert(int u, int v, int w);
	std::vector<int>* dijkstra(int s);
};

