#pragma once
#include "Node.h"
#include <algorithm>
#include <vector>
#include <stack>
#include <utility>

//#define TEST_MODE

template <typename T, typename Compare = std::less<T>>
class AVL {
private:
	Node<T>* root;
	int n;
	int son(Node<T>* node) {
		if (node->fa == NULL) {
			return -1;
		}
		return node == (node->fa->child[1]);
	}
	void pushup(Node<T>* node) {
		if (node == NULL) {
			return;
		}
		node->size = node->cnt;
		node->depth = 1;
		node->tag = 0;
		if (hasLeftChild(node)) {
			node->size += node->child[0]->size;
			node->depth = std::max(node->depth, node->child[0]->depth + 1);
			node->tag = node->child[0]->depth;
		}
		if (hasRightChild(node)) {
			node->size += node->child[1]->size;
			node->depth = std::max(node->depth, node->child[1]->depth + 1);
			node->tag = node->tag - node->child[1]->depth;
		}
	}
	void rotate(Node<T>* node)
	{
		//x:node  y:nodeFa  z:nodeFaFa
		Node<T>* nodeFa = node->fa, *nodeFaFa = NULL;
		if (nodeFa != NULL) nodeFaFa = nodeFa->fa;
		int b = son(node), c = son(nodeFa);
		Node<T>* a = node->child[!b];
		if (nodeFaFa != NULL) {
			nodeFaFa->child[c] = node;
		}
		else {
			root = node;
		}
		node->fa = nodeFaFa;
		if (a != NULL) {
			a->fa = nodeFa;
		}
		nodeFa->child[b] = a;
		node->child[!b] = nodeFa;
		nodeFa->fa = node;

		pushup(nodeFa);
		pushup(node);
	}
	void pushupAll(Node<T>* node) {
		if (node == NULL) {
			return;
		}
		do {
			pushup(node);
			node = node->fa;
		} while (node != NULL);
	}
	void rotateAllForInsert(Node<T>* node) {
		if (node == NULL || node->fa == NULL || node->fa->fa == NULL) {
			pushupAll(node);
			return;
		}
		Node<T> *nodeFa = node->fa, *nodeFaFa = node->fa->fa;
		pushup(node);
		pushup(nodeFa);
		while (nodeFaFa != NULL) {
			pushup(nodeFaFa);
			if (abs(nodeFaFa->tag) > 1) {
				if (son(node) == son(nodeFa)) {
					rotate(nodeFa);
					pushupAll(nodeFa);
				}
				else {
					rotate(node);
					rotate(node);
					pushupAll(node);
				}
				break;
			}
			node = nodeFa;
			nodeFa = nodeFaFa;
			nodeFaFa = nodeFa->fa;
		}
	}
	void rotateAllForDelt(Node<T>* node) {
		if (node == NULL) {
			return;
		}
		while (node != NULL) {
			/*if (node->tag == 2) {
				auto tmp = node->child[0];
				if (tmp->tag == 1 || tmp->tag == 0) {
					rotate(tmp);
				}
				else if (tmp->tag == -1) {
					tmp = tmp->child[1];
					rotate(tmp);
					rotate(tmp);
				}
			}
			else if (node->tag == -2) {
				auto tmp = node->child[1];
				if (tmp->tag == -1 || tmp->tag == 0) {
					rotate(tmp);
				}
				else if (tmp->tag == 1) {
					tmp = tmp->child[0];
					rotate(tmp);
					rotate(tmp);
				}
			}*/

			pushup(node);
			auto freshNode = node->fa;
			if (node->tag == 2 || node->tag == -2) {
				int a = (node->tag < 0);
				auto child = node->child[a];
				if (child->tag * node->tag < 0) {
					auto tmp = child->child[!a];
					rotate(tmp);
					rotate(tmp);
					freshNode = tmp;
				}
				else {
					rotate(child);
					freshNode = child;
				}
				//break;
			}
			node = freshNode;
		}
	}
	
	//查询排名为k的数
	T getK(Node<T>* node, int k) {
		auto left = node->child[0];
		int size = 0;
		if (left != NULL) {
			size = left->size;
		}
		if (size + 1 <= k && k <= size + node->cnt) {
			return node->data;
		}
		else if (size + 1 > k) {
			return getK(node->child[0], k);
		}
		else {
			return getK(node->child[1], k - (size + node->cnt));
		}
	}

public:
	int size() {
		return n;
	}
	bool empty() {
		return n == 0;
	}
	AVL() :root(NULL), n(0) {}
	void insert(T data) {
		Compare cmp;
		Node<T>* nowNode = root;
		++n;

		if (root == NULL) {
			root = new Node<T>(data);
			return;
		}

		while (true) {
			T nowData = nowNode->data;
			if (data == nowData) {
				++(nowNode->cnt);
				pushupAll(nowNode);
				break;
			}
			else if (cmp(data, nowData)) {
				if (!hasLeftChild(nowNode)) {
					nowNode->child[0] = new Node<T>(data, nowNode);
					rotateAllForInsert(nowNode->child[0]);
					break;
				}
				else {
					nowNode = nowNode->child[0];
				}
			}
			else {
				if (!hasRightChild(nowNode)) {
					nowNode->child[1] = new Node<T>(data, nowNode);
					rotateAllForInsert(nowNode->child[1]);
					break;
				}
				else {
					nowNode = nowNode->child[1];
				}
			}
		}
	}
	void delt(T data) {
		Compare cmp;
		Node<T>* nowNode = root;
		while (nowNode != NULL) {
			if (nowNode->data == data) {
				--n;
				if (nowNode->cnt > 1) {
					--nowNode->cnt;
					pushupAll(nowNode);
				}
				else {
					//如果既没有左儿子也没有右儿子
					if ((!hasLeftChild(nowNode)) && (!hasRightChild(nowNode))) {
						Node<T>* nowNodeFa = nowNode->fa;
						if (nowNodeFa == NULL) {
							root = NULL;
						}
						else {
							nowNode->fa->child[son(nowNode)] = NULL;
						}
						delete nowNode;
						pushupAll(nowNodeFa);
						rotateAllForDelt(nowNodeFa);
					}
					//如果没有左儿子但有右儿子
					else if (!hasLeftChild(nowNode)) {
						//删除
						if (nowNode->fa == NULL) {
							root = nowNode->child[1];
							nowNode->child[1]->fa = NULL;
						}
						else {
							int a = son(nowNode);
							nowNode->fa->child[a] = nowNode->child[1];
							nowNode->child[1]->fa = nowNode->fa;

							pushupAll(nowNode->fa->child[a]);
							rotateAllForDelt(nowNode->fa->child[a]);
						}
						delete nowNode;
					}
					//如果有左儿子
					else {
						Node<T>* tmpNode = nowNode->child[0];
						//找到最大的
						tmpNode = findMax(tmpNode);
						Node<T>* tmpNodeFa;
						tmpNodeFa = tmpNode->fa;

						Node<T>* freshNode;

						if (tmpNodeFa != nowNode) {
							freshNode = tmpNodeFa;

							tmpNodeFa->child[1] = tmpNode->child[0];
							if (tmpNode->child[0] != NULL) {
								tmpNode->child[0]->fa = tmpNodeFa;
							}

							tmpNode->child[0] = nowNode->child[0];
							if (nowNode->child[0] != NULL) {
								nowNode->child[0]->fa = tmpNode;
							}

							tmpNode->child[1] = nowNode->child[1];
							if (nowNode->child[1] != NULL) {
								nowNode->child[1]->fa = tmpNode;
							}
						}
						else {
							freshNode = tmpNode;

							tmpNode->child[1] = nowNode->child[1];
							if (nowNode->child[1] != NULL) {
								nowNode->child[1]->fa = tmpNode;
							}
						}

						if (nowNode->fa == NULL) {
							root = tmpNode;
							tmpNode->fa = NULL;
						}
						else {
							if (isLeftChild(nowNode->fa, nowNode)) {
								nowNode->fa->child[0] = tmpNode;
								tmpNode->fa = nowNode->fa;
							}
							else {
								nowNode->fa->child[1] = tmpNode;
								tmpNode->fa = nowNode->fa;
							}
						}

						pushupAll(freshNode);
						rotateAllForDelt(freshNode);
						delete nowNode;
					}
				}
				break;
			}
			if (cmp(data, nowNode->data)) {
				if (!hasLeftChild(nowNode)) {
					break;
				}
				nowNode = nowNode->child[0];
			}
			else {
				if (!hasRightChild(nowNode)) {
					break;
				}
				nowNode = nowNode->child[1];
			}
		}
	}

	//查询x的排名
	int getRank(T x) {
		Compare cmp;
		auto node = root;
		int sum = 0;
		while (node != NULL) {
			if (node->data == x) {
				if (node->child[0] != NULL) {
					return sum + node->child[0]->size + 1;
				}
				else return sum + 1;
			}
			if (cmp(x, node->data)) {
				node = node->child[0];
			}
			else {
				if (node->child[0] != NULL) {
					sum += node->child[0]->size;
				}
				sum += node->cnt;
				node = node->child[1];
			}
		}
		return sum + 1;
		
	}
	//查询排名为k的数
	T getK(int k) {
		return getK(root, k);
	}
	//获得比x小的第一个数
	T getPre(T x) {
		Compare cmp;
		auto node = root;
		T ans;
		while (node != NULL) {
			if (cmp(x, node->data) || x == node->data) {
				node = node->child[0];
			}
			else {
				ans = node->data;
				node = node->child[1];
			}
		}
		return ans;
	}
	//获得x的后继
	T getSuc(T x) {
		Compare cmp;
		auto node = root;
		T ans;
		while (node != NULL) {
			if (cmp(node->data, x) || x == node->data) {
				node = node->child[1];
			}
			else {
				ans = node->data;
				node = node->child[0];
			}
		}
		return ans;
	}

#ifdef TEST_MODE
	//测试用
	int _getDep() {
		if (root == NULL) {
			return 0;
		}
		return root->depth;
	}

	int _getTag() {
		if (root == NULL) {
			return 0;
		}
		return root->tag;
	}

	bool testNode(Node<T>* node) {
		if (node == NULL) {
			return false;
		}

		int size, depth, tag;
		size = node->cnt;
		depth = 1;
		tag = 0;
		if (hasLeftChild(node)) {
			size += node->child[0]->size;
			depth = std::max(depth, node->child[0]->depth + 1);
			tag = node->child[0]->depth;
		}
		if (hasRightChild(node)) {
			size += node->child[1]->size;
			depth = std::max(depth, node->child[1]->depth + 1);
			tag = tag - node->child[1]->depth;
		}

		return (size != node->size) || (depth != node->depth) || (tag != node->tag);
	}

	bool testAll(Node<T> * node) {
		/*if (node == NULL) {
			return false;
		}
		return (node->tag >= 2 || node->tag <= -2) || testAll(node->child[0]) || testAll(node->child[1]);*/
		
		if (node == NULL) {
			return false;
		}
		return testNode(node) || testAll(node->child[0]) || testAll(node->child[1]);

	}

	bool testAll() {
		return testAll(root);
	}
#endif // TESTMODE


	

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


template <class T>
bool hasLeftChild(Node<T>* node) {
	if (node == NULL) {
		return false;
	}
	return !(node->child[0] == NULL);
}
template <class T>
bool hasRightChild(Node<T>* node) {
	if (node == NULL) {
		return false;
	}
	return !(node->child[1] == NULL);
}

template <class T>
bool isLeftChild(Node<T>* fa, Node<T>* son) {
	if (fa == NULL || son == NULL) {
		return false;
	}
	if (fa->child[0] == son) {
		return true;
	}
	return false;
}
template <class T>
bool isRightChild(Node<T>* fa, Node<T>* son) {
	if (fa == NULL || son == NULL) {
		return false;
	}
	if (fa->child[1] == son) {
		return true;
	}
	return false;
}

template <class T>
Node<T>* findMin(Node<T>* fa) {
	if (fa == NULL) {
		return NULL;
	}
	while (hasLeftChild(fa)) {
		fa = fa->child[0];
	}
	return fa;
}
template <class T>
Node<T>* findMax(Node<T>* fa) {
	if (fa == NULL) {
		return NULL;
	}
	while (hasRightChild(fa)) {
		fa = fa->child[1];
	}
	return fa;
}

template <class T, typename Function>
void inorderTraversal(const AVL<T>& bst, Function f) {
	inorderTraversal(bst.root, f);
}
template <class T, typename Function>
void inorderTraversal(Node<T>* node, Function f) {
	std::stack<std::pair<Node<T>*, bool>> stack;
	if (node == NULL) {
		return;
	}
	stack.push(std::make_pair(node, false));
	while (!stack.empty()) {
		std::pair<Node<T>*, bool> tmp = stack.top();
		Node<T>* tmpNode = tmp.first;
		bool tmpBool = tmp.second;
		stack.pop();
		if (!tmpBool) {
			stack.push(std::make_pair(tmpNode, true));
			if (tmpNode->child[0] != NULL) {
				stack.push(std::make_pair(tmpNode->child[0], false));
			}
		}
		else {
			f(tmpNode->data, tmpNode->cnt);
			if (tmpNode->child[1] != NULL) {
				stack.push(std::make_pair(tmpNode->child[1], false));
			}
		}
	}

	return;
}
