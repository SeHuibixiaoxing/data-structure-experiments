#include "Graph.h"
#include "DisjointSet.h"
#include <algorithm>

Graph::Graph(int n, int m) {
	this->n = n;
	this->m = m;
	cnt = 0;
	edge.resize((m << 1) + 1);
	head.resize(n + 1);
}

void Graph::insert(int u, int v, int w) {
	edge[++cnt] = Edge(u, v, w, head[u]);
	head[u] = cnt;
	edge[++cnt] = Edge(v, u, w, head[v]);
	head[v] = cnt;
}

std::vector<Edge>* Graph::getMST() {
	std::vector<Edge>* re = new std::vector<Edge>();
	std::vector<int>* tag = new std::vector<int>();
	DisjointSet disjointSet(n);

	for (int i = 0; i <= cnt; ++i) {
		tag->push_back(i);
	}

	std::sort(tag->begin() + 1, tag->begin() + cnt + 1, [&](int a, int b){
		return edge[a].w < edge[b].w;
		});

	int tot = 0;
	for (int i = 1; i <= cnt; ++i) {
		int j = (*tag)[i];
		int u = edge[j].u, v = edge[j].v;
		if (!disjointSet.isSame(u, v)) {
			++tot;
			(*re).push_back(edge[j]);
			disjointSet.merge(u, v);
		}

		if (tot == n - 1) {
			break;
		}
	}

	delete tag;

	return re;
}

void Graph::getEulerDfs(int x, std::vector<Edge>& ans, std::vector<bool>& vis) {
	for (int pos = head[x]; pos; pos = edge[pos].next) {
		if (vis[pos]) continue;

		//¼ì²éposÊÇ·ñÎªÇÅ
		int isBridge = false;
		DisjointSet* disjointSet = new DisjointSet(n);
		for (int i = 1; i <= cnt; i += 2) {
			if ((!vis[i]) && i != pos && getAnother(i) != pos) {
				disjointSet->merge(edge[i].u, edge[i].v);
			}
		}
		int tmp1 = disjointSet->getSetNum();
		disjointSet->merge(edge[pos].u, edge[pos].v);
		int tmp2 = disjointSet->getSetNum();
		if (tmp1 != tmp2) continue;
		delete disjointSet;

		vis[pos] = vis[getAnother(pos)] = true;
		ans.push_back(edge[pos]);
		getEulerDfs(edge[pos].v, ans, vis);
	}

	for (int pos = head[x]; pos; pos = edge[pos].next) {
		if (vis[pos]) continue;
		vis[pos] = true;
		vis[getAnother(pos)] = true;
		ans.push_back(edge[pos]);
		getEulerDfs(edge[pos].v, ans, vis);
	}
	return;
}

std::vector<Edge>* Graph::getEuler() {
	std::vector<int> degree;
	degree.resize(n + 1, 0);
	for (int i = 1; i <= cnt; ++i) {
		++ degree[edge[i].u];
	}
	for (int i = 1; i <= n; ++i) {
		if (degree[i] % 2 == 1) {
			return nullptr;
		}
	}
	
	DisjointSet disjointSet(n);
	for (int i = 1; i <= cnt; ++i) {
		disjointSet.merge(edge[i].u, edge[i].v);
	}
	if (disjointSet.getSetNum() > 1) {
		return nullptr;
	}

	std::vector<bool> vis;
	vis.resize(cnt + 1, false);
	std::vector<Edge>* re = new std::vector<Edge>();
	getEulerDfs(1, *re, vis);
	return re;

}
