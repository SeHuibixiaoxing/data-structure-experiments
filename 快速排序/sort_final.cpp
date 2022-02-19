#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "Stack.h"



//[first, last)
template<typename T, typename Compare>
void sort(T* first, T* last, Compare cmp) {
	class State {
	public:
		T *l, *mid, *r;				//[l, mid)   [mid, r) 
		State(T* _l = NULL, T* _r = NULL, T* _mid = NULL) : l(_l), r(_r), mid(_mid) {}
	};
	

	//	[l, r)
	class sort_mid_class {
	public:
		class swap_class {
		public:
			void operator()(T* a, T* b) {
				T tmp = *a;
				*a = *b;
				*b = tmp;
			}
		}swap;

		T* operator()(T* l, T* r, Compare cmp) {
			if (l == r - 1) return r;
			
			srand(time(0));
			T* tmp = (rand() % (r - l)) + l; 
			swap(l, tmp);
			
			T *p = l + 1, *q = r - 1, *mid = r;			//[p, q]

			if (p == q) {
				if (!cmp(*l, *q)) {
					swap(l, q);
				}
				return p;
			}

			while (p < q) {
				while (!cmp(*q, *l) && p < q) --q;
				while (cmp(*p, *l) && p < q) ++p;
				if (p == q) {
					if (cmp(*q, *l)) {
						swap(l, q);
						mid = q;
					}
					else {
						mid = l;
					} 
				}
				else {
					swap(p, q);
				}
			}
			return mid;
		}
	}sort_mid;

	Stack<State> stack;

	stack.push(State(first, last));

	while (!stack.empty()) {
		State now = stack.top();
		stack.pop();
		if (now.l + 1 >= now.r) {
			continue;
		}
		
		T* mid = sort_mid(now.l, now.r, cmp);

		if (now.l < mid - 1) {
			stack.push(State(now.l, mid));
		}
		if (mid + 1 < now.r) {
			stack.push(State(mid + 1, now.r));
		}
	}
}


template<typename T>
void sort(T* first, T* last) {
	class cmp {
	public:
		bool operator()(T first, T last) {
			return first < last;
		}
	};
	sort(first, last, cmp());
}

int a[1000], b[1000];

int main() {
	//使用间接排序测试 
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	
	for (int i = 0; i < n; ++i) {
		b[i] = i;
	}
	
	//a相等时按b排序
	class comp {
	public: 
		bool operator()(int x, int y) {
			return a[x] < a[y];
		}
	};
	
	sort(b, b + n, comp());
	
	for(int i = 0;i < n;++ i) {
		printf("%d ", a[b[i]]);
	}
	printf("\n");
	
	for (int i = 0; i < n; ++i) {
		printf("%d ", b[i]);
	}
	printf("\n");

	return 0;
}


