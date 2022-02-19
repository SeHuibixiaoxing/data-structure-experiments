#ifndef Queueh
#define Queueh

#include "DoubleLinkedList.h"

#endif

template<class T>
class Queue {
	private:
		DoubleLinkedList<T> list;
		int n;
	public:
		Queue() {
			n = 0;
		}
		int size() {
			return n;
		}
		T front() {		
			return list.front(); 
		} 
		void pop() {
			if(n > 0) -- n;
			list.removeFront(); 
		}
		void push(T x) {
			++ n;
			list.insertBack(x);
		}
		bool empty() {
			return n == 0;
		}
};





 
