#include "DisjointSet.h"

DisjointSet::DisjointSet(int n)
{
	reset(n);
}

int DisjointSet::size()
{
	return n;
}

int DisjointSet::getSetNum() {
	return setNum;
}

bool DisjointSet::empty()
{
	return n == 0;
}

int DisjointSet::find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void DisjointSet::merge(int a, int b)
{
	int f1 = find(a), f2 = find(b);
	if (f1 == f2) {
		return;
	}
	--setNum;
	if (height[a] < height[b]) {
		fa[f1] = f2;
	}
	else if (height[b] < height[a]) {
		fa[f2] = f1;
	}
	else {
		fa[f1] = f2;
		++height[f2];
	}
}

bool DisjointSet::isSame(int a, int b)
{
	return find(a) == find(b);
}

void DisjointSet::reset(int n) {
	fa.clear();
	height.clear();

	this->n = n;
	fa.resize(n + 1, 0);
	height.resize(n + 1, 0);
	for (int i = 0; i <= n; ++i) {
		fa[i] = i;
	}
	setNum = n;
}


