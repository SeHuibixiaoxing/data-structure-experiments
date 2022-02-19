#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

template<typename> class Node;
template<typename> class Iterator;
template<typename> class DoubleLinkedList;


template<class T>
class Node {
private:
	Node* pre, * next;
	T data;
	Node(T data, Node* pre = NULL, Node* next = NULL) : data(data), pre(pre), next(next) {}
	friend class DoubleLinkedList<T>;
	friend class Iterator<T>;
};
template<class T>
class Iterator {
private:
	Node<T>* node;
	Iterator(Node<T>* node) {
		this->node = node;
	}
	bool next() {
		if (node == NULL || node->next == NULL) return false;
		node = node->next;
		return true;
	}
	bool pre() {
		if (node == NULL || node->pre == NULL) return false;
		node = node->pre;
		return true;
	}
	bool equal(Iterator node) {
		return this->node == node;
	}

public:
	T get() {
		return node->data;
	}
	Iterator<T> operator+(const int b) {
		Iterator<T> re;
		for (int i = 0; i < b; ++i) {
			re.next();
		}
		return re;
	}
	Iterator<T> operator-(const int b) {
		Iterator<T> re(this->node);
		for (int i = 0; i < b; ++i) {
			re.pre();
		}
		return re;
	}
	Iterator<T> operator++() {
		Iterator<T> re(this->node);
		re.next();
		this->next();
		return re;
	}
	Iterator<T> operator++(int) {
		Iterator<T> re(this->node);
		this->next();
		return re;
	}
	Iterator<T> operator--() {
		Iterator<T> re(this->node);
		re.pre();
		this.pre();
		return re;
	}
	Iterator<T> operator--(int) {
		Iterator<T> re(this->node);
		this->pre();
		return re;
	}
	bool operator ==(const Iterator& b) {
		return b.node == this->node;
	}
	bool operator !=(const Iterator& b) {
		return b.node != this->node;
	}
	friend class DoubleLinkedList<T>;
};

template<class T>
class DoubleLinkedList {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	DoubleLinkedList() {
		head = tail = NULL;
	}
	DoubleLinkedList(const DoubleLinkedList& list) {
		printf("Copy function has been run\n");
		head = tail = NULL;
		for (Node<T>* cur = list.head; cur != NULL; cur = cur->next) {
			insertBack(cur->data);
		}
	}
	~DoubleLinkedList() {
		for (Node<T>* cur = head; cur != NULL;) {
			Node<T>* tmp = cur->next;
			delete cur;
			cur = tmp;
		}
	}
	bool isEmpty() const {
		return head == NULL;
	}
	Iterator<T> begin() {
		return Iterator<T>(head);
	}
	Iterator<T> end() {
		return Iterator<T>(tail);
	}
	//插入到iterator位置前面,如果为NULL则必然没有元素，将iterator移至新添加元素，否则iterator位置不变 
	void insertFront(T x, Iterator<T>& iterator) {
		Node<T>* p = iterator.node;
		if (p == NULL) {
			head = tail = new Node<T>(x);
			iterator.node = head;
		}
		else {
			Node<T>* cur = new Node<T>(x, p->pre, p);
			if (p->pre == NULL) {
				head = cur;
				p->pre = cur;
			}
			else {
				p->pre->next = cur;
				p->pre = cur;
			}
		}
	}
	//插入到链表头
	void insertFront(T x) {
		Iterator<T> tmp = this->begin();
		insertFront(x, tmp);
	}
	//插入到interator位置后面，如果为NULL则必然没有元素，将iterator移至新添加元素，否则iterator位置不变  
	void insertBack(T x, Iterator<T>& iterator) {
		Node<T>* p = iterator.node;
		if (p == NULL) {
			head = tail = new Node<T>(x);
			iterator.node = head;
		}
		else {
			Node<T>* cur = new Node<T>(x, p, p->next);
			if (p->next == NULL) {
				p->next = cur;
				tail = cur;
			}
			else {
				p->next->pre = cur;
				p->next = cur;
			}
		}
	}
	//插入到链表尾 
	void insertBack(T x) {
		Iterator<T> tmp = this->end();
		insertBack(x, tmp);
	}
	//删除interator位置元素，默认移动到下一位，没有下一位则移动到上一位，没有上一位则NULL 
	void remove(Iterator<T>& iterator) {
		Node<T>* p = iterator.node;
		if (p == NULL) {
			head = tail = NULL;
			return;
		}

		if (p->next != NULL) {
			iterator.next();
		}
		else if (p->pre != NULL) {
			iterator.pre();
		}
		else {
			head = tail = NULL;
			iterator.node = NULL;
		}

		if (p->pre == NULL && p->next != NULL) {
			head = p->next;
			head->pre = NULL;
		}
		else if (p->next == NULL && p->pre != NULL) {
			tail = p->pre;
			tail->next = NULL;
		}
		else if (p->next == NULL && p->pre == NULL) {
			head = tail = NULL;
			return;
		}
		else {
			p->pre->next = p->next;
			p->next->pre = p->pre;
		}
		delete p;
	}
	//返回头元素 
	T front() {
		return head->data;
	}
	//返回尾元素 
	T back() {
		return tail->data;
	}
	//移除头元素 
	void removeFront() {
		Iterator<T> tmp = this->begin();
		remove(tmp);
	}
	//移除尾元素 
	void removeBack() {
		Iterator<T> tmp = this->end();
		remove(tmp);
	}
};


