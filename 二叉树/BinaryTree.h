#pragma once
#include "Node.h"
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <utility>

template <class T>
class BinaryTree
{
private:
	Node<T>* root;
	int n;
	void clear(Node<T>* node) {
		if (node != NULL) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}


	//data记录前序遍历中对应结点的数据
	Node<T>* creatPreMidMain(const std::vector<int>& preString, const std::vector<int>& midString, const std::vector<T>& data, int preL, int preR, int midL, int midR) {
		if ((midR - midL) != (preR - preL) || (midR - midL + 1) <= 0) {
			return NULL;
		}

		Node<T> *re = Node<T>::build(data[preL]); 
		int p = midL;
		while (midString[p] != preString[preL]) { 
			++p;
		}

		re->left = creatPreMidMain(preString, midString, data,
			preL + 1, preL + (p - midL), 
			midL, p - 1);
		if (re->left != NULL) {
			re->left->fa = re;
		}
		re->right = creatPreMidMain(preString, midString, data,
			preL + (p - midL) + 1, preL + (p - midL) + (midR - p),
			p + 1, midR);
		if (re->right != NULL) {
			re->right->fa = re;
		}
		return re;
	}

public:
	int size() {
		return n;
	}
	bool empty() {
		return n == 0;
	}

	
	void creatPreMid(const std::vector<int>& preString, const std::vector<int>& midString, const std::vector<T>& data = preString) {
		this->n = preString.size();
		root = creatPreMidMain(preString, midString, data, 0, preString.size() - 1, 0, midString.size() - 1);
	}

	void clear() {
		clear(root);
	}

	~BinaryTree() {
		clear();
	}

	template <typename T, typename Function>
	friend void preorderTraversal(const BinaryTree<T>& tree, Function f);

	template<typename T, typename Function>
	friend void inorderTraversal(const BinaryTree<T>& tree, Function f);

	template<typename T, typename Function>
	friend void postorderTraversal(const BinaryTree<T>& tree, Function f);

};

template<typename T,typename Function>
void preorderTraversal(const BinaryTree<T>& tree, Function f) {
	std::stack<std::pair<Node<T>*, bool>> stack;
	if (tree.root == NULL) {
		return;
	}
	stack.push(std::make_pair(tree.root, false));
	f(tree.root->data);
	while (!stack.empty()) {
		std::pair<Node<T>*, bool> tmp = stack.top();
		Node<T>* tmpNode = tmp.first;
		bool tmpBool = tmp.second;
		stack.pop();
		if (!tmpBool) {
			stack.push(std::make_pair(tmpNode, true));
			if (tmpNode->left != NULL) {
				stack.push(std::make_pair(tmpNode->left, false));
				f(tmpNode->left->data);
			}
		}
		else {
			if (tmpNode->right != NULL) {
				stack.push(std::make_pair(tmpNode->right, false));
				f(tmpNode->right->data);
			}
		}
	}
}


template<typename T, typename Function>
void inorderTraversal(const BinaryTree<T>& tree, Function f) {
	std::stack<std::pair<Node<T>*, bool>> stack;
	if (tree.root == NULL) {
		return;
	}
	stack.push(std::make_pair(tree.root, false));
	while (!stack.empty()) {
		std::pair<Node<T>*, bool> tmp = stack.top();
		Node<T>* tmpNode = tmp.first;
		bool tmpBool = tmp.second;
		stack.pop();
		if (!tmpBool) {
			stack.push(std::make_pair(tmpNode, true));
			if (tmpNode->left != NULL) {
				stack.push(std::make_pair(tmpNode->left, false));
			}
		}
		else {
			f(tmpNode->data);
			if (tmpNode->right != NULL) {
				stack.push(std::make_pair(tmpNode->right, false));
			}
		}
	}
}

template<typename T, typename Function>
void postorderTraversal(const BinaryTree<T>& tree, Function f) {
	std::stack<std::pair<Node<T>*, int>> stack;
	if (tree.root == NULL) {
		return;
	}
	stack.push(std::make_pair(tree.root, 0));
	while (!stack.empty()) {
		std::pair<Node<T>*, int> tmp = stack.top();
		Node<T>* tmpNode = tmp.first;
		int tmpBool = tmp.second;
		stack.pop();
		if (tmpBool == 0) {
			stack.push(std::make_pair(tmpNode, 1));
			if (tmpNode->left != NULL) {
				stack.push(std::make_pair(tmpNode->left, 0));
			}
		}
		else if(tmpBool == 1) {
			stack.push(std::make_pair(tmpNode, 2));
			if (tmpNode->right != NULL) {
				stack.push(std::make_pair(tmpNode->right, 0));
			}
		}
		else {
			f(tmpNode->data);
		}
	}
}
