#pragma once

#include "Node.h"
#include <vector>
#include <algorithm>
#include <utility>

//#define DEBUG_MODE

template<class T, class Compare = std::less<T>>
class TwoThreeTree {
	Node<T, Compare>* root = nullptr;
	Compare cmp;

	int son(Node<T, Compare>* node) {
		if (node == nullptr || node->fa == nullptr) {
			return -1;
		}
		if (node->fa->type >= 2 && node == node->fa->child[0]) {
			return 0;
		}
		else if (node->fa->type >= 2 && node == node->fa->child[1]) {
			return 1;
		}
		else if (node->fa->type == 3 && node == node->fa->child[2]) {
			return 2;
		}
		return -1;
	}

	void pushup(Node<T, Compare>* node) {
		if (node == nullptr) {
			return;
		}
		if (node->child == nullptr) {
			if (node->type == 2) {
				node->size = node->cnt[0];
			}
			else if (node->type == 3) {
				node->size = node->cnt[0] + node->cnt[1];
			}
			else if (node->type == 4) {
				node->size = node->cnt[0] + node->cnt[1];
			}
		}
		else {
			if (node->type == 2) {
				node->size = node->cnt[0] + node->child[0]->size + node->child[1]->size;
			}
			else if (node->type == 3) {
				node->size = node->cnt[0] + node->cnt[1] + node->child[0]->size + node->child[1]->size + node->child[2]->size;
			}
			else if (node->type == 4) {
				node->size = node->cnt[0] + node->cnt[1] + node->cnt[2] + node->child[0]->size + node->child[1]->size + node->child[2]->size + node->child[3]->size;
			}
		}		
	}

	void pushupAll(Node<T, Compare>* node) {
		while (node != nullptr) {
			pushup(node);
			node = node->fa;
		}
	}

	//node节点中data值代表空节点
	void deltLeaf(Node<T, Compare>* node, T data) {
		if (node->type == 3) {
			int tag = -1;
			if (node->data[0] == data) {
				tag = 1;
			}
			else if(node->data[1] == data) {
				tag = 0;
			}
			node->creat2(node->data[tag], node->cnt[tag], nullptr, nullptr, node->fa);
			pushupAll(node);
		}
		else if (node->type == 2) {
			if (node->fa == nullptr) {
				root = nullptr;
				delete node;
				return;
			}

			std::vector<std::pair<T, int>> tmp;
			Node<T, Compare>* fa = node->fa;

			if (fa->type == 2) {
				int tag = son(node);
				tmp.push_back(std::make_pair(fa->data[0], fa->cnt[0]));
				Node<T, Compare>* son = fa->child[!tag];
				if (son->type == 2) {
					tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
				}
				else if (son->type == 3) {
					tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
					tmp.push_back(std::make_pair(son->data[1], son->cnt[1]));
				}

				delete son;
				delete node;
			}
			else if (fa->type == 3) {
				int tag = son(node);
				tmp.push_back(std::make_pair(fa->data[0], fa->cnt[0]));
				tmp.push_back(std::make_pair(fa->data[1], fa->cnt[1]));
				Node<T, Compare>* son = fa->child[(tag + 1) % 3];
				if (son->type == 2) {
					tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
				}
				else if (son->type == 3) {
					tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
					tmp.push_back(std::make_pair(son->data[1], son->cnt[1]));
				}
				auto mid = fa->child[(tag + 2) % 3];
				if (mid->type == 2) {
					tmp.push_back(std::make_pair(mid->data[0], mid->cnt[0]));
				}
				else if (mid->type == 3) {
					tmp.push_back(std::make_pair(mid->data[0], mid->cnt[0]));
					tmp.push_back(std::make_pair(mid->data[1], mid->cnt[1]));
				}

				delete son;
				delete mid;
				delete node;
			}
			
			std::sort(tmp.begin(), tmp.end(), [&](std::pair<T, int> a, std::pair<T, int> b) {
				return cmp(a.first, b.first);
				});

			if (tmp.size() == 3) {
				Node<T, Compare>* node1 = new Node<T, Compare>();
				Node<T, Compare>* node2 = new Node<T, Compare>();
				node1->creat2(tmp[0].first, tmp[0].second, nullptr, nullptr, fa);
				node2->creat2(tmp[2].first, tmp[2].second, nullptr, nullptr, fa);
				fa->creat2(tmp[1].first, tmp[1].second, node1, node2, fa->fa);
				pushupAll(fa);
			}
			else if (tmp.size() == 4) {
				Node<T, Compare>* node1 = new Node<T, Compare>();
				Node<T, Compare>* node2 = new Node<T, Compare>();
				node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, nullptr, nullptr, nullptr, fa);
				node2->creat2(tmp[3].first, tmp[3].second, nullptr, nullptr, fa);
				fa->creat2(tmp[2].first, tmp[2].second, node1, node2, fa->fa);
				pushupAll(fa);
			}
			else if (tmp.size() == 5) {
				Node<T, Compare>* node1 = new Node<T, Compare>();
				Node<T, Compare>* node2 = new Node<T, Compare>();
				node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, nullptr, nullptr, nullptr, fa);
				node2->creat3(tmp[3].first, tmp[4].first, tmp[3].second, tmp[4].second, nullptr, nullptr, nullptr, fa);
				fa->creat2(tmp[2].first, tmp[2].second, node1, node2, fa->fa);
				pushupAll(fa);
			}
			else if (tmp.size() == 6) {
				Node<T, Compare>* node1 = new Node<T, Compare>();
				Node<T, Compare>* node2 = new Node<T, Compare>();
				Node<T, Compare>* node3 = new Node<T, Compare>();
				node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, nullptr, nullptr, nullptr, fa);
				node2->creat2(tmp[3].first, tmp[3].second, nullptr, nullptr, fa);
				node3->creat2(tmp[5].first, tmp[5].second, nullptr, nullptr, fa);
				fa->creat3(tmp[2].first, tmp[4].first, tmp[2].second, tmp[4].second, node1, node2, node3, fa->fa);
				pushupAll(fa);
			}
			else if (tmp.size() == 2) {
				Node<T, Compare>* node1 = new Node<T, Compare>();
				node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, nullptr, nullptr, nullptr, fa);
				fa->creat0(node1, fa->fa);

				Node<T, Compare>* now = fa;

				while (now->type == 0 && now->fa != nullptr) {
					std::vector<std::pair<T, int>> tmp;
					std::vector<Node<T, Compare>*> child;
					Node<T, Compare>* fa = now->fa;
					child.push_back(now->child[0]);

					if (fa->type == 2) {
						int tag = son(now);
						tmp.push_back(std::make_pair(fa->data[0], fa->cnt[0]));
						Node<T, Compare>* son = fa->child[!tag];
						if (son->type == 2) {
							tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
							child.push_back(son->child[0]);
							child.push_back(son->child[1]);
						}
						else if (son->type == 3) {
							tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
							tmp.push_back(std::make_pair(son->data[1], son->cnt[1]));
							child.push_back(son->child[0]);
							child.push_back(son->child[1]);
							child.push_back(son->child[2]);
						}

						delete fa->child[!tag];
						delete now;
					}
					else if (fa->type == 3) {
						int tag = son(now);
						tmp.push_back(std::make_pair(fa->data[0], fa->cnt[0]));
						tmp.push_back(std::make_pair(fa->data[1], fa->cnt[1]));
						Node<T, Compare>* son = fa->child[(tag + 1) % 3];
						if (son->type == 2) {
							tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
							child.push_back(son->child[0]);
							child.push_back(son->child[1]);
						}
						else if (son->type == 3) {
							tmp.push_back(std::make_pair(son->data[0], son->cnt[0]));
							tmp.push_back(std::make_pair(son->data[1], son->cnt[1]));
							child.push_back(son->child[0]);
							child.push_back(son->child[1]);
							child.push_back(son->child[2]);
						}
						auto mid = fa->child[(tag + 2) % 3];
						if (mid->type == 2) {
							tmp.push_back(std::make_pair(mid->data[0], mid->cnt[0]));
							child.push_back(mid->child[0]);
							child.push_back(mid->child[1]);
						}
						else if (mid->type == 3) {
							tmp.push_back(std::make_pair(mid->data[0], mid->cnt[0]));
							tmp.push_back(std::make_pair(mid->data[1], mid->cnt[1]));
							child.push_back(mid->child[0]);
							child.push_back(mid->child[1]);
							child.push_back(mid->child[2]);
						}

						delete fa->child[(tag + 1) % 3];
						delete fa->child[(tag + 2) % 3];
						delete now;
					}

					std::sort(tmp.begin(), tmp.end(), [&](std::pair<T, int> a, std::pair<T, int> b) {
						return cmp(a.first, b.first);
						});
					std::sort(child.begin(), child.end(), [&](Node<T, Compare>* a, Node<T, Compare>* b) {
						return cmp(a->data[0], b->data[0]);
						});


					if (tmp.size() == 3) {
						Node<T, Compare>* node1 = new Node<T, Compare>();
						Node<T, Compare>* node2 = new Node<T, Compare>();
						node1->creat2(tmp[0].first, tmp[0].second, child[0], child[1], fa);
						node2->creat2(tmp[2].first, tmp[2].second, child[2], child[3], fa);
						fa->creat2(tmp[1].first, tmp[1].second, node1, node2, fa->fa);
						pushupAll(fa);
						break;
					}
					else if (tmp.size() == 4) {
						Node<T, Compare>* node1 = new Node<T, Compare>();
						Node<T, Compare>* node2 = new Node<T, Compare>();
						node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, child[0], child[1], child[2], fa);
						node2->creat2(tmp[3].first, tmp[3].second, child[3], child[4], fa);
						fa->creat2(tmp[2].first, tmp[2].second, node1, node2, fa->fa);
						pushupAll(fa);
						break;
					}
					else if (tmp.size() == 5) {
						Node<T, Compare>* node1 = new Node<T, Compare>();
						Node<T, Compare>* node2 = new Node<T, Compare>();
						node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, child[0], child[1], child[2], fa);
						node2->creat3(tmp[3].first, tmp[4].first, tmp[3].second, tmp[4].second, child[3], child[4], child[5], fa);
						fa->creat2(tmp[2].first, tmp[2].second, node1, node2, fa->fa);
						pushupAll(fa);
						break;
					}
					else if (tmp.size() == 6) {
						Node<T, Compare>* node1 = new Node<T, Compare>();
						Node<T, Compare>* node2 = new Node<T, Compare>();
						Node<T, Compare>* node3 = new Node<T, Compare>();
						node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, child[0], child[1], child[2], fa);
						node2->creat2(tmp[3].first, tmp[3].second, child[3], child[4], fa);
						node3->creat2(tmp[5].first, tmp[5].second, child[5], child[6], fa);
						fa->creat3(tmp[2].first, tmp[4].first, tmp[2].second, tmp[4].second, node1, node2, node3, fa->fa);
						pushupAll(fa);
						break;
					}
					else if (tmp.size() == 2) {
						Node<T, Compare>* node1 = new Node<T, Compare>();
						node1->creat3(tmp[0].first, tmp[1].first, tmp[0].second, tmp[1].second, child[0], child[1], child[2], fa);
						fa->creat0(node1, fa->fa);

						now = fa;
					}
				}
				if (now->fa == nullptr) {
					root = now->child[0];
					now->child[0]->fa = nullptr;
					delete now;
				}
			}
		}
	}

public:
	int size() {
		if (root == nullptr) {
			return 0;
		}
		return root->size;
	}
	bool empty() {
		return root == nullptr;
	}
   	void insert(T data) {
		if (root == nullptr) {
			root = new Node<T, Compare>();
			root->creat2(data, 1, nullptr, nullptr, nullptr);
#ifdef DEBUG_MODE
			printf("%d\n", this->size());
#endif // DEBUG_MODE
			return;
		}

		Node<T, Compare>* now = root;

		while (true) {
			if (now->type == 2) {
				if (data == now->data[0]) {
					++now->cnt[0];
					pushupAll(now);
#ifdef DEBUG_MODE
					printf("%d\n", this->size());
#endif // DEBUG_MODE
					return;
				}
				else if (now->child == nullptr) {
					break;
				}
				else if (cmp(data, now->data[0])) {
					now = now->child[0];
				}
				else {
					now = now->child[1];
				}
			}
			else if (now->type == 3) {
				if (data == now->data[0]) {
					++now->cnt[0];
					pushupAll(now);
#ifdef DEBUG_MODE
					printf("%d\n", this->size());
#endif // DEBUG_MODE
					return;
				}
				else if(data == now->data[1]) {
					++now->cnt[1];
					pushupAll(now);
#ifdef DEBUG_MODE
					printf("%d\n", this->size());
#endif // DEBUG_MODE
					return;
				}
				else if (now->child == nullptr) {
					break;
				}
				else if (cmp(data, now->data[0])) {
					now = now->child[0];
				}
				else if (cmp(data, now->data[1])) {
					now = now->child[1];
				}
				else {
					now = now->child[2];
				}
			}
		}

		if (now->type == 2) {
			if (cmp(now->data[0], data)) {
				now->creat3(now->data[0], data, now->cnt[0], 1, nullptr, nullptr, nullptr, now->fa);
			}
			else {
				now->creat3(data, now->data[0], 1, now->cnt[0], nullptr, nullptr, nullptr, now->fa);
			}
			pushupAll(now);
#ifdef DEBUG_MODE
			printf("%d\n", this->size());
#endif // DEBUG_MODE
			return;

		}
		else if (now->type == 3) {
			T tmp[3];
			int cnt[3];
			tmp[0] = data, tmp[1] = now->data[0], tmp[2] = now->data[1];
			cnt[0] = 1, cnt[1] = now->cnt[0], cnt[2] = now->cnt[1];
			if (!cmp(tmp[0], tmp[1])) {
				std::swap(tmp[0], tmp[1]);
				std::swap(cnt[0], cnt[1]);
				if (!cmp(tmp[1], tmp[2])) {
					std::swap(tmp[1], tmp[2]);
					std::swap(cnt[1], cnt[2]);
				}
			}		

			if (now->fa == nullptr) {
				Node<T, Compare>* node1 = new Node<T, Compare>();
				Node<T, Compare>* node2 = new Node<T, Compare>();
				Node<T, Compare>* node3 = new Node<T, Compare>();
				node2->creat2(tmp[0], cnt[0], nullptr, nullptr, node1);
				node3->creat2(tmp[2], cnt[2], nullptr, nullptr, node1);
				node1->creat2(tmp[1], cnt[1], node2, node3, nullptr);
				delete root;
				root = node1;
			}
			else if(now->fa->type == 2){
				Node<T, Compare>* d1 = now;
				Node<T, Compare>* fa = now->fa;

				Node<T, Compare>* node1 = new Node<T, Compare>();
				Node<T, Compare>* node2 = new Node<T, Compare>();

				node1->creat2(tmp[0], cnt[0], nullptr, nullptr, fa);
				node2->creat2(tmp[2], cnt[2], nullptr, nullptr, fa);

				if (fa->child[0] == now) {
					fa->creat3(tmp[1], fa->data[0], cnt[1], fa->cnt[0], node1, node2, fa->child[1], fa->fa);
				}
				else if (fa->child[1] == now) {
					fa->creat3(fa->data[0], tmp[1], fa->cnt[0], cnt[1], fa->child[0], node1, node2, fa->fa);
				}

				pushupAll(fa);

				delete d1;
			}
			else if (now->fa->type == 3) {
				now->creat4(tmp[0], tmp[1], tmp[2], cnt[0], cnt[1], cnt[2], nullptr, nullptr, nullptr, nullptr, now->fa);
				
				while (now->fa != nullptr && now->fa->type == 3) {
					Node<T, Compare>* d1 = now;
					Node<T, Compare>* fa = now->fa;

					Node<T, Compare>* node1 = new Node<T, Compare>();
					Node<T, Compare>* node2 = new Node<T, Compare>();
					if (now->child == nullptr) {
						node1->creat2(now->data[0], now->cnt[0], nullptr, nullptr, fa);
						node2->creat2(now->data[2], now->cnt[2], nullptr, nullptr, fa);
					}
					else {
						node1->creat2(now->data[0], now->cnt[0], now->child[0], now->child[1], fa);
						node2->creat2(now->data[2], now->cnt[2], now->child[2], now->child[3], fa);	
						now->child[0]->fa = now->child[1]->fa = node1;
						now->child[2]->fa = now->child[3]->fa = node2;
					}
					if (fa->child[0] == now) {
						fa->creat4(now->data[1], fa->data[0], fa->data[1], now->cnt[1], fa->cnt[0], fa->cnt[1], node1, node2, fa->child[1], fa->child[2], fa->fa);
					}
					else if (fa->child[1] == now) {
						fa->creat4(fa->data[0], now->data[1], fa->data[1], fa->cnt[0], now->cnt[1], fa->cnt[1], fa->child[0], node1, node2, fa->child[2], fa->fa);
					}
					else if (fa->child[2] == now) {
						fa->creat4(fa->data[0], fa->data[1], now->data[1], fa->cnt[0], fa->cnt[1], now->cnt[1], fa->child[0], fa->child[1], node1, node2, fa->fa);
					}

					now = fa;

					delete d1;
				}

				Node<T, Compare>* d1 = now;
				Node<T, Compare>* fa = now->fa;

				Node<T, Compare>* node1 = new Node<T, Compare>();
				Node<T, Compare>* node2 = new Node<T, Compare>();
				node1->creat2(now->data[0], now->cnt[0], now->child[0], now->child[1], fa);
				node2->creat2(now->data[2], now->cnt[2], now->child[2], now->child[3], fa);

				if (now->fa == nullptr) {
					root->creat2(now->data[1], now->cnt[1], node1, node2, nullptr);
				}
				else if (now->fa->type == 2) {				
					if (fa->child[0] == now) {
						fa->creat3(now->data[1], fa->data[0], now->cnt[1], fa->cnt[0], node1, node2, fa->child[1], fa->fa);
					}
					else if (fa->child[1] == now) {
						fa->creat3(fa->data[0], now->data[1], fa->cnt[0], now->cnt[1], fa->child[0], node1, node2, fa->fa);
					}
					delete d1;
					pushupAll(fa);
				}
			}
		}
#ifdef DEBUG_MODE
		printf("%d\n", this->size());
#endif // DEBUG_MODE

		return;
	}


	void delt(T data) {
		Node<T, Compare>* now = root;

		while (true) {
			if (now->type == 2) {
				if (data == now->data[0]) {
					if (now->cnt[0] > 1) {
						now->cnt[0] -= 1;
						pushupAll(now);
#ifdef DEBUG_MODE
						printf("%d\n", this->size());
#endif // DEBUG_MODE
						return;
					}
					if (now->child == nullptr) {
						deltLeaf(now, data);
					}
					else {
						Node<T, Compare>* tmp = now;
						now = now->child[1];
						while (now->child != nullptr) {
							now = now->child[0];
						}
						std::swap(tmp->data[0], now->data[0]);
						std::swap(tmp->cnt[0], now->cnt[0]);
						deltLeaf(now, now->data[0]);
					}
#ifdef DEBUG_MODE
					printf("%d\n", this->size());
#endif // DEBUG_MODE
					return;
				}
				else if (now->child == nullptr) {
#ifdef DEBUG_MODE
					printf("%d\n", this->size());
#endif // DEBUG_MODE
					return;
				}
				else if (cmp(data, now->data[0])) {
					now = now->child[0];
				}
				else {
					now = now->child[1];
				}
			}
			else if (now->type == 3) {
				if (data == now->data[0]) {
					if (now->cnt[0] > 1) {
						now->cnt[0] -= 1;
						pushupAll(now);
#ifdef DEBUG_MODE
						printf("%d\n", this->size());
#endif // DEBUG_MODE
						return;
					}
					if (now->child == nullptr) {
						deltLeaf(now, data);
					}
					else {
						Node<T, Compare>* tmp = now;
						now = now->child[1];
						while (now->child != nullptr) {
							now = now->child[0];
						}
						std::swap(tmp->data[0], now->data[0]);
						std::swap(tmp->cnt[0], now->cnt[0]);
						deltLeaf(now, now->data[0]);
					}
#ifdef DEBUG_MODE
					printf("%d\n", this->size());
#endif // DEBUG_MODE
					return;
				}
				else if (data == now->data[1]) {
					if (now->cnt[1] > 1) {
						now->cnt[1] -= 1;
						pushupAll(now);
#ifdef DEBUG_MODE
						printf("%d\n", this->size());
#endif // DEBUG_MODE
						return;
					}
					if (now->child == nullptr) {
						deltLeaf(now, data);
					}
					else {
						Node<T, Compare>* tmp = now;
						now = now->child[2];
						while (now->child != nullptr) {
							now = now->child[0];
						}
						std::swap(tmp->data[1], now->data[0]);
						std::swap(tmp->cnt[1], now->cnt[0]);
						deltLeaf(now, now->data[0]);
					}
#ifdef DEBUG_MODE
					printf("%d\n", this->size());
#endif // DEBUG_MODE
					return;
				}
				else if (now->child == nullptr) {
					return;
				}
				else if (cmp(data, now->data[0])) {
					now = now->child[0];
				}
				else if (cmp(data, now->data[1])) {
					now = now->child[1];
				}
				else {
					now = now->child[2];
				}
			}
		}
#ifdef DEBUG_MODE
		printf("%d\n", this->size());
#endif // DEBUG_MODE


	}


	template <class T, typename Compare, typename Function>
	friend void inorderTraversal(const TwoThreeTree<T, Compare>& bst, Function f);
	template <class T, typename Compare, typename Function>
	friend void inorderTraversal(Node<T, Compare>* node, Function f);

};


template <class T, typename Compare, typename Function>
void inorderTraversal(const TwoThreeTree<T, Compare>& bst, Function f) {
	inorderTraversal(bst.root, f);
}
template <class T, typename Compare, typename Function>
void inorderTraversal(Node<T, Compare>* node, Function f) {
	if (node == nullptr) {
		return;
	}
	if (node->type == 2) {
		if (node->child == nullptr) {
			f(node->data[0], node->cnt[0]);
			return;
		}
		else {
			inorderTraversal(node->child[0], f);
			f(node->data[0], node->cnt[0]);
			inorderTraversal(node->child[1], f);
			return;
		}
	}
	else if (node->type == 3) {
		if (node->child == nullptr) {
			f(node->data[0], node->cnt[0]);
			f(node->data[1], node->cnt[1]);
			return;
		}
		else {
			inorderTraversal(node->child[0], f);
			f(node->data[0], node->cnt[0]);
			inorderTraversal(node->child[1], f);
			f(node->data[1], node->cnt[1]);
			inorderTraversal(node->child[2], f);
			return;
		}
	}

	return;
}
