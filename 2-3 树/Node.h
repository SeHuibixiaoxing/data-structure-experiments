#pragma once
#include <algorithm>

template<class T, class Compare = std::less<T>>
class Node
{
	Node<T, Compare>** child = NULL;		//儿子结点
	int size = 0;				
	T* data = NULL;
	int* cnt = NULL;
	Node<T, Compare>* fa = NULL;
	int type = 0;

	Compare cmp;

	void clear() {
		if (child != nullptr) {
			delete[] child;
			child = nullptr;
		}
		if (data != nullptr) {
			delete[] data;
			data = NULL;
		}
		if (cnt != nullptr) {
			delete cnt;
			cnt = NULL;
		}
		type = size = 0;
	}

	//要求data1 < data2 < data3，四个孩子节点按顺序。不会真实存在，必须以各种方式被拆分
	void creat4(T data1, T data2, T data3, int cnt1, int cnt2, int cnt3, Node<T, Compare>* left, Node<T, Compare>* midLeft, Node<T, Compare>* midRight, Node<T, Compare>* right, Node<T, Compare>* fa) {
		clear();
		size = cnt1 + cnt2 + cnt3;
		data = new T[3];
		data[0] = data1;
		data[1] = data2;
		data[2] = data3;
		cnt = new int[3];
		cnt[0] = cnt1;
		cnt[1] = cnt2;
		cnt[2] = cnt3;
		this->fa = fa;
		type = 4;
		if (left == NULL) {
			child = NULL;
		}
		else {
			child = new Node<T, Compare> * [4];
			child[0] = left;
			child[1] = midLeft;
			child[2] = midRight;
			child[3] = right;
			left->fa = midLeft->fa = midRight->fa = right->fa = this;
			size += left->size + midLeft->size + midRight->size + right->size;
		}
	}
	//要求cmp(data1, data2) == true  三个孩子结点按顺序
	void creat3(T data1, T data2, int cnt1, int cnt2, Node<T, Compare>* left, Node<T, Compare>* mid, Node<T, Compare>* right, Node<T, Compare>* fa) {
		clear();
		size = cnt1 + cnt2;
		data = new T[2];
		data[0] = data1;
		data[1] = data2;
		cnt = new int[2];
		cnt[0] = cnt1;
		cnt[1] = cnt2;
		this->fa = fa;
		type = 3;
		if (left == NULL) {
			child = NULL;
		}
		else {
			child = new Node<T, Compare> * [3];
			child[0] = left;
			child[1] = mid;
			child[2] = right;
			left->fa = mid->fa = right->fa = this;
			size += left->size + mid->size + right->size;
		}
	}
	//要求两个孩子结点按顺序
	void creat2(T data1, int cnt1, Node<T, Compare>* left, Node<T, Compare>* right, Node<T, Compare>* fa) {
		clear();
		size = cnt1;
		data = new T[1];
		data[0] = data1;
		cnt = new int[1];
		cnt[0] = cnt1;
		this->fa = fa;
		type = 2;
		if (left == NULL) {
			child = NULL;
		}
		else {
			child = new Node<T, Compare> * [2];
			child[0] = left;
			child[1] = right;
			left->fa = right->fa = this;
			size += left->size + right->size;
		}
	}
	//只有一个儿子，节点为空，不会真实存在
	void creat0(Node<T, Compare>* child, Node<T, Compare>* fa) {
		clear();
		this->size = 0;
		this->fa = fa;
		this->type = 0;
		if (child == NULL) {
			this->child = NULL;
		}
		else {
			this->child = new Node<T, Compare> * [1];
			this->child[0] = child;
			child->fa = this;
			this->size += child->size;
		}
	}

	~Node() {
		clear();
	}

	template<class T, class Compare = std::less<T>>
	friend class TwoThreeTree;
	template <class T, typename Compare, typename Function>
	friend void inorderTraversal(const TwoThreeTree<T, Compare>& bst, Function f);
	template <class T, typename Compare, typename Function>
	friend void inorderTraversal(Node<T, Compare>* node, Function f);
};

