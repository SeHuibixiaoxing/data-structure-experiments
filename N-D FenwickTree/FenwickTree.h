#pragma once
 
#include <vector>
#include <stack>
#include <utility>
#include <cstdio>
#include <stdarg.h>
#include <algorithm>

//#define DEBUG_MODE

//以加法群的形式表示，需要给类型T定义+、-运算，并传入单位元
template <class T>
class FenwickTreeAdd {
private:
	//内部顺序为低维->高维
	//对外顺序为高维->低维
	//对外接口从0开始
	//对内操作从1开始
	//内部存储从0开始

	std::vector<T> data;
	int dimension;
	std::vector<T> dimensionSize;
	std::vector<T> dimensionSizeSum;
	T identityElement;
	int n;

	//将dimension维映射到一维
	int rank(const std::vector<int>& r) {
		int sum = 1, re = 0;
		int j = 0;
		for (int i = 0; i < r.size(); ++i, ++ j) {
			re += (r[i] - 1) * sum;
			sum *= dimensionSizeSum[j];
		}
		return re;
	}

	T get(const std::vector<int>& r) {
		/*
		for(int an = r[n]; an >= 0; an -= lowbit(an))
			for(int an-1 = r[n]; an-1 >= 0; an-1 -= lowbit(an))
				...
					for(int a0 = r[0]; a0 >= 0; a0 -= lowbit(0))
						sum += data[rank()];		
		*/
		std::vector<int> tmp;
		for (int i = 0; i < this->dimension; ++i) {
			tmp.push_back(0);
		}
		std::stack<std::pair<int, int>> stack;
		stack.push(std::make_pair(this->dimension - 1, r[this->dimension - 1]));
		T sum = this->identityElement;
		while (!stack.empty()) {
			auto now = stack.top();
			stack.pop();
			if (now.first == 0) {
				if (now.second < 1) {
					continue;
				}
				else {
					tmp[now.first] = now.second;

#ifdef DEBUG_MODE
					for (auto i = tmp.begin(); i != tmp.end(); ++i) {
						printf("%d, ", *i);
					}
					printf("\n");
#endif // DEBUG_MODE
					sum += data[rank(tmp)];
					stack.push(std::make_pair(now.first, now.second - lowbit(now.second)));
				}
			}
			else {
				int nxt = now.second - lowbit(now.second);
				tmp[now.first] = now.second;
				if (nxt >= 1) {
					stack.push(std::make_pair(now.first, nxt));
				}
				stack.push(std::make_pair(now.first - 1, r[now.first - 1]));
			}
		}

		return sum;
	}

	void modifyAdd(const std::vector<int>& r, T val) {
		/*
		for(int an = r[n]; an <= dimensionSize[n]; an += lowbit(an))
			for(int an-1 = r[n-1]; an-1 <= dimensionSize[n-1]; an-1 += lowbit(an))
				...
					for(int a0 = r[0]; a0 <= dimensionSize[0]; a0 += lowbit(0))
						sum += data[rank()];
		*/

		std::vector<int> tmp;
		for (int i = 0; i < this->dimension; ++i) {
			tmp.push_back(0); 
		}
		std::stack<std::pair<int, int>> stack;
		stack.push(std::make_pair(this->dimension - 1, r[this->dimension - 1]));
		T sum = this->identityElement;
		while (!stack.empty()) {
			auto now = stack.top();
			stack.pop();
			if (now.first == 0) {
				if (now.second > this->dimensionSize[0]) {
					continue;
				}
				else {
					tmp[now.first] = now.second;

#ifdef DEBUG_MODE
					for (auto i = tmp.begin(); i != tmp.end(); ++i) {
						printf("%d, ", *i);
					}
					printf("\n");
#endif // DEBUG_MODE
					data[rank(tmp)] += val;
					stack.push(std::make_pair(now.first, now.second + lowbit(now.second)));
				}
			}
			else {
				int nxt = now.second + lowbit(now.second);
				tmp[now.first] = now.second;
				if (nxt <= this->dimensionSize[now.first]) {
					stack.push(std::make_pair(now.first, nxt));
				}
				stack.push(std::make_pair(now.first - 1, r[now.first - 1]));
			}
		}
	}


	int lowbit(int x) {
		return x & (-x);
	}

public:
	FenwickTreeAdd(T identityElement, int dimension, ...) {
		this->dimension = dimension;
		this->identityElement = identityElement;

		va_list ap;  //声明一个va_list变量
		va_start(ap, dimension);  //第二个参数表示形参的个数

		int cnt = dimension;

		for (int i = 0; i < dimension; ++i) {
			int tmp = va_arg(ap, int);
			this->dimensionSize.push_back(tmp);
		}

		std::reverse(dimensionSize.begin(), dimensionSize.end());
		dimensionSizeSum.push_back(dimensionSize[0]);
		for (int i = 1; i < dimension; ++i) {
			this->dimensionSizeSum.push_back(this->dimensionSizeSum[i - 1] + this->dimensionSize[i]);
		}

		va_end(ap);  //用于清理		

		int mul = 1;
		for (auto i = this->dimensionSize.begin(); i != this->dimensionSize.end(); ++i) {
			mul *= (*i);
		}
		for (auto i = mul - 1; i >= 0; --i) {
			this->data.push_back(this->identityElement);
		}
	}



	T get(int dimensionSize, ...) {

		int size = 0;

		std::vector<int> r;

		va_list ap;
		va_start(ap, dimensionSize);

		int tmp = dimensionSize;
		r.push_back(tmp);
		for (int i = 1; i < this->dimension; ++i) {
			int tmp = va_arg(ap, int);
			r.push_back(tmp);
		}

		va_end(ap);
		std::reverse(r.begin(), r.end());
		for (auto i = r.begin(); i != r.end(); ++i) {
			(*i) += 1;
		}
		return get(r);
	}

	void modifyAdd(int val, int dimensionSize, ...) {

		int size = 0;

		std::vector<int> r;

		va_list ap;
		va_start(ap, dimensionSize);

		int tmp = dimensionSize;
		r.push_back(tmp);
		for (int i = 1; i < this->dimension; ++i) {
			int tmp = va_arg(ap, int);
			r.push_back(tmp);
		}

		va_end(ap);
		std::reverse(r.begin(), r.end());
		for (auto i = r.begin(); i != r.end(); ++i) {
			(*i) += 1;
		}
		modifyAdd(r,val);
	}


	int getDimension() {
		return dimension;
	}
	int getSize() {
		return data.size();
	}
	int getDimensionSize(int rank) {
		return dimensionSize[rank];
	}

};



