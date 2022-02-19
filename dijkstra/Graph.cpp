#include "Graph.h"

void Graph::insert(int u, int v, int w) {
	if (edge.empty()) {
		edge.push_back(Edge(0, 0, 0, 0));
	}
	while (head.size() <= u || head.size() <= v) head.push_back(0);
	edge.push_back(Edge(u, v, w, head[u]));
	head[u] = edge.size() - 1;
}

std::vector<int>* Graph::dijkstra(int s) {
	std::vector<int>* d = new std::vector<int>();
	std::vector<bool>* b = new std::vector<bool>();
	std::priority_queue<Node, std::vector<Node>, cmp> q;
	while (d->size() <= s) {
		d->push_back(INF);
	}
	while (b->size() <= s) {
		b->push_back(false);
	}
	q.push(Node(s, 0));
	(*d)[s] = 0;
	while (!q.empty()) {
		Node now = q.top();
		q.pop();
		if ((*b)[now.v]) continue;
		(*b)[now.v] = true;
		for (int pos = head[now.v]; pos; pos = edge[pos].next) {
			int v = edge[pos].v;
			while (d->size() <= v) {
				d->push_back(INF);
			}
			while (b->size() <= v) {
				b->push_back(false);
			}
			if ((*b)[v]) continue;
			if ((*d)[v] > (*d)[now.v] + edge[pos].w) {
				(*d)[v] = (*d)[now.v] + edge[pos].w;
				q.push(Node(v, (*d)[v]));
			}
		}
	}
	delete b;
	return d;
}
