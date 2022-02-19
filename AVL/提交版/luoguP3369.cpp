#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>
#include <utility>


template <class T>
class Node {
public:
	T data;
	Node<T>* child[2], * fa;
	int cnt, depth, size, tag;
	Node(const T& data, Node<T>* fa = NULL, int depth = 1, Node<T>* leftChild = NULL, Node<T>* rightChild = NULL, int cnt = 1, int size = 1, int tag = 0) : 
		data(data), fa(fa), depth(depth), cnt(cnt), size(size), tag(tag) {
		child[0] = leftChild;
		child[1] = rightChild;
	}
};

template <typename T, typename Compare = std::less<T>>
class AVL {
public:
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
		if (size + 1 > k) {
			return getK(node->child[0], k);
		}
		if (size + node->cnt < k) {
			return getK(node->child[1], k - (size + node->cnt));
		}
	}
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



int main() {

	AVL<int> avl;

	//printf("输入初始元素个数:\n");
	//int n;
	//scanf("%d", &n);
	//printf("输入初始元素:\n");
	//for (int i = 0; i < n; ++i) {
	//	int tmp;
	//	scanf("%d", &tmp);
	//	avl.insert(tmp);
	//}
	//inorderTraversal(avl, [](int val, int cnt) {
	//	printf("value = %d, cnt = %d\n", val, cnt);
	//	});
	//while (true) {
	//	printf("1:插入;2:删除;3:输出正中序遍历;4:查询x的排名;5:查询排名为x的数;6:求x的前驱;7:求x的后继;其它:退出\n");
	//	int tag = 0;
	//	scanf("%d", &tag);
	//	if (tag == 1) {
	//		printf("输入插入元素(整数)：\n");
	//		int num;
	//		scanf("%d", &num);
	//		avl.insert(num);
	//	}
	//	else if (tag == 2) {
	//		printf("输入删除元素(整数)：\n");
	//		int num;
	//		scanf("%d", &num);
	//		avl.delt(num);
	//	}
	//	else if (tag == 3) {
	//		printf("正中序遍历\n");
	//		inorderTraversal(avl, [](int val, int cnt) {
	//			printf("value = %d, cnt = %d\n", val, cnt);
	//			});
	//	}
	//	else if (tag == 4) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getRank(num));
	//	}
	//	else if (tag == 5) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getK(num));
	//	}
	//	else if (tag == 6) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getPre(num));
	//	}
	//	else if (tag == 7) {
	//		int num;
	//		scanf("%d", &num);
	//		printf("%d\n", avl.getSuc(num));
	//	}
	//	else {
	//		break;
	//	}
	//}
	freopen("data.txt", "r", stdin);
	int t = 0;
	scanf("%d", &t);
	while (t) {
		--t;
		int tag = 0;
		scanf("%d", &tag);
		if (tag == 1) {
			int num;
			scanf("%d", &num);
			avl.insert(num);
		}
		else if (tag == 2) {
			int num;
			scanf("%d", &num);
			avl.delt(num);
		}
		else if (tag == 3) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getRank(num));
		}
		else if (tag == 4) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getK(num));
		}
		else if (tag == 5) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getPre(num));
		}
		else if (tag == 6) {
			int num;
			scanf("%d", &num);
			printf("%d\n", avl.getSuc(num));
		}
	}

	return 0;
}
