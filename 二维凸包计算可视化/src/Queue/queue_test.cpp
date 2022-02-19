#include "Queue.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

int main(){
	Queue<int> queue;
	printf("%d\n", queue.size());
	for(int i = 0;i < 10;++ i) {
		queue.push(i);
	}
	printf("%d\n", queue.size());
	for(int i = 0;i < 10;++ i) {
		printf("%d ", queue.front());
		queue.pop();
	}	
	printf("\n%d\n", queue.size());
	return 0; 	
}
