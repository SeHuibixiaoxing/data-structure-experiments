#ifndef Stackh
#define Stackh

#include "DoubleLinkedList.h"

#endif

template<class T>
class Stack {
private:
	DoubleLinkedList<T> list;
	int n;
public:
	Stack() {
		n = 0;
	}
	int size() {
		return n;
	}
	T top() {
		return list.back();
	}
	void pop() {
		if (n > 0) --n;
		list.removeBack();
	}
	void push(T x) {
		++n;
		list.insertBack(x);
	}
	bool empty() {
		return n == 0;
	}
};


