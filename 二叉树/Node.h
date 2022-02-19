#pragma once

#define NULL 0

template<class T>
class Node
{
private:
	Node *left, *right, *fa;
	T data;
	Node(const T& data, Node* left = NULL, Node* right = NULL, Node* fa = NULL) :data(data), left(left), right(right), fa(fa){}
	static Node<T>* build(const T& data, Node* left = NULL, Node* right = NULL, Node* fa = NULL) {
		Node<T>* tmp = new Node(data, left, right, fa);
		return tmp;
	}
	
public:
	template <class T>
	friend class BinaryTree;


	template<typename T, typename Function>
	friend void preorderTraversal(const BinaryTree<T>& tree, Function f);

	template<typename T, typename Function>
	friend void inorderTraversal(const BinaryTree<T>& tree, Function f);

	template<typename T, typename Function>
	friend void postorderTraversal(const BinaryTree<T>& tree, Function f);
};

