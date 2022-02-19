#include "Stack.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

int main(){
	Stack<int> stack;
	printf("%d\n", stack.size());
	for(int i = 0;i < 10;++ i) {
		stack.push(i);
	}
	printf("%d\n", stack.size());
	for(int i = 0;i < 10;++ i) {
		printf("%d ", stack.top());
		stack.pop();
	}	
	printf("\n%d\n", stack.size());
	return 0; 	
}
