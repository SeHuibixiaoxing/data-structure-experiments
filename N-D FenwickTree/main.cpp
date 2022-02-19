#define _CRT_SECURE_NO_WARNINGS 

#include "FenwickTree.h"
#include <cstdio>


int main() {

	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);


	int n, m;
	scanf("%d %d", &n, &m);

	FenwickTreeAdd<long long> tree(0, 2, n, m);
	int tmp;
	while (scanf("%d", &tmp) != EOF) {
		if (tmp == 1) {
			int x, y, k;
			scanf("%d %d %d", &x, &y, &k);
			--x;
			--y;
			tree.modifyAdd(k, x, y);
		}
		else if (tmp == 2) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			--x1;
			--y1;
			--x2;
			--y2;
			long long ans;
			if (x1 == 0 && y1 == 0) {
				ans = tree.get(x2, y2);
			}
			else if (x1 == 0) {
				ans = tree.get(x2, y2) - tree.get(x2, y1 - 1);
			}
			else if (y1 == 0) {
				ans = tree.get(x2, y2) - tree.get(x1 - 1, y2);
			}
			else {
				ans = tree.get(x2, y2) - tree.get(x1 - 1, y2) - tree.get(x2, y1 - 1) + tree.get(x1 - 1, y1 - 1);
			}
			printf("%lld\n", ans);
		}
	}

}

