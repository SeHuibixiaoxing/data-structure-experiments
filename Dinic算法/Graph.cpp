#include "Graph.h"

int Graph::getAnother(int pos) {
	return pos ^ 1;
}

Graph::Graph(int S, int T, int n) {
	edge.push_back(Edge(0, 0, 0, 0));
	edge.push_back(Edge(0, 0, 0, 0));
	head.push_back(0);
	this->S = S;
	this->T = T;
	this->n = n;
	head.resize(n + 1);
	m = 0;
}

void Graph::insert(int u, int v, int w) {
	++m;
	edge.push_back(Edge(u, v, w, head[u]));
	head[u] = edge.size() - 1;
	edge.push_back(Edge(v, u, 0, head[v]));
	head[v] = edge.size() - 1;
}

int Graph::dfsForFordFulkerson(int x, int mi, std::vector<bool>& vis) {
	if (x == T) {
		return mi;
	}
	for (int pos = head[x]; pos; pos = edge[pos].next) {
		int v = edge[pos].v;
		if (vis[v] || edge[pos].w == 0) {
			continue;
		}
		vis[v] = true;
		int tmp;
		if (mi == -1) {
			tmp = edge[pos].w;
		}
		else {
			tmp = std::min(mi, edge[pos].w);
		}
		int w = dfsForFordFulkerson(v, tmp, vis);
		if (w != -1) {
			edge[pos].w -= w;
			edge[pos ^ 1].w += w;
			vis[v] = false;
			return w;
		}
		vis[v] = false;
	}
	return -1;
}

bool Graph::bfs() {
	h.resize(n + 1, -1);
	std::fill(h.begin(), h.end(), -1);
	h[S] = 0;
	std::vector<int> q;
	int begin = 0;
	q.push_back(S);
	while (begin < q.size()) {
		int now = q[begin ++];
		for (int pos = head[now]; pos; pos = edge[pos].next) {
			int v = edge[pos].v;
			if (edge[pos].w && h[v] == -1) {
				h[v] = h[now] + 1;
				q.push_back(v);
			}
		}
	}
	return h[T] != -1;
}

int Graph::dfsForDinic(int x, int f) {
	if (x == T || f == 0) {
		return f;
	}
	int used = 0, w;
	for (int pos = head[x]; pos; pos = edge[pos].next) {
		int v = edge[pos].v;
		if (h[v] == h[x] + 1 && edge[pos].w > 0) {
			w = dfsForDinic(v, std::min(edge[pos].w, f - used));
			if (w > 0) {
				edge[pos].w -= w;
				edge[pos ^ 1].w += w;
				used += w;
			}
			if (used == f) {
				return f;
			}
		}
	}
	if (!used) h[x] = -1;
	return used;
}

int Graph::runFordFulkerson() {
	int ans = 0;
	std::vector<bool> vis;
	vis.resize(n + 1, false);
	vis[S] = true;
	int w = dfsForFordFulkerson(S, -1, vis);
	while (w != -1) {
		ans += w;
		w = dfsForFordFulkerson(S, -1, vis);
	}
	return ans;
}

int Graph::runDinic() {
	int ans = 0;
	while (bfs()) {
		ans += dfsForDinic(S, 0x3f3f3f3f);
	}
	return ans;
}


