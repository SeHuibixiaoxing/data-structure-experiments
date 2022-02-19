#pragma once
#define NULL 0
#include "AVL.h"

template <class T>
class Node {
private:
	T data;
	Node<T>* child[2], * fa;
	int cnt, depth, size, tag;
	Node(const T& data, Node<T>* fa = NULL, int depth = 1, Node<T>* leftChild = NULL, Node<T>* rightChild = NULL, int cnt = 1, int size = 1, int tag = 0) : 
		data(data), fa(fa), depth(depth), cnt(cnt), size(size), tag(tag) {
		child[0] = leftChild;
		child[1] = rightChild;
	}
public:

	template <typename T, typename Compare = std::less<T>>
	friend class AVL;

	template <class T, typename Function>
	friend void inorderTraversal(const AVL<T>& bst, Function f);

	template <class T, typename Function>
	friend void inorderTraversal(Node<T>* node, Function f);

	template <class T>
	friend bool hasLeftChild(Node<T>* node);

	template <class T>
	friend bool hasRightChild(Node<T>* node);

	template <class T>
	friend bool isLeftChild(Node<T>* fa, Node<T>* son);

	template <class T>
	friend bool isRightChild(Node<T>* fa, Node<T>* son);

	template <class T>
	friend Node<T>* findMin(Node<T>* fa);

	template <class T>
	friend Node<T>* findMax(Node<T>* fa);


};