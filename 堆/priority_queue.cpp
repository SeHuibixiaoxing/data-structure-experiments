#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>

template<typename T, typename List = std::vector<T>,
	typename Compare = std::less<typename List::value_type>>
	class priority_queue {
	private:
		Compare cmp;
		List list;
		int n;
		void UpMove(int rank) {
			int now = rank;
			while (now > 1) {
				int fa = (now >> 1);
				if (cmp(list[fa], list[now])) {
					T tmp = list[fa];
					list[fa] = list[now];
					list[now] = tmp;
					now = fa;
					//					std::swap(list[fa], list[now]);
				}
				else {
					break;
				}
			}
		}

		void DownMove(int rank) {
			int now = rank;
			while (now < n) {
				int l = now << 1, r = now << 1 | 1;
				int min;
				if (l > n) {
					break;
				}
				else if (r > n) {
					min = l;
				}
				else if (!cmp(list[l], list[r])) {
					min = l;
				}
				else {
					min = r;
				}

				if (cmp(list[now], list[min])) {
					T tmp = list[now];
					list[now] = list[min];
					list[min] = tmp;
					now = min;
				}
				else {
					break;
				}
			}
		}

	public:
		priority_queue() {
			n = 0;
		}

		bool empty() {
			return n == 0;
		}

		int size() {
			return n;
		}

		void push(T x) {
			if (n == 0 && list.empty())	list.push_back(x);
			++n;
			list.push_back(x);
			UpMove(n);
		}

		T top() {
			return list[1];
		}

		void pop() {
			T tmp = list[1];
			list[1] = list[n];
			list[n] = tmp;
			list.pop_back();
			--n;
			DownMove(1);
		}



};

struct cmp {
	bool operator()(int a, int b){
		return a > b;
	}
};

priority_queue<int, std::vector<int>, cmp> q;

int main() {
	freopen("D:\\材料\\学堂课程资料\\大二上\\数据结构\\作业\\06 堆\\data.txt", "r", stdin);

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; ++i) {
		int pos;
		scanf("%d", &pos);
		if (pos == 1) {
			int x;
			scanf("%d", &x);
			q.push(x);
		}
		else if (pos == 2) {
			printf("%d\n", q.top());
		}
		else {
			q.pop();
		}
	}

	return 0;
}


