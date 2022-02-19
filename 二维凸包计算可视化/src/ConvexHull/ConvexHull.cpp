#include "Stack.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

const int INF = 0x3f3f3f3f;
const double eps = 1e-8;

class Point {
public:
	double x, y;
	int num;
	Point(int num, double x, double y): x(x), y(y), num(num){}
	Point(){x = y = 0;num = 0;}
};

class Line {
public:
	Point a, b;
	double theta;
	Line(){}
	Line(Point node1, Point node2) {
		a = node1;
		b = node2;
		theta = atan2(b.y - a.y, b.x - a.x); 
	}
};

bool cmp(Line& a, Line& b) {
	return a.theta < b.theta;
}
	
Point vec(int num, Point node1, Point node2) {
	Point re(num, (node2.x - node1.x), (node2.y - node1.y));
	return re;
}

double cross(Point vec1, Point vec2) {
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

double distance(Point node1, Point node2) {
	return sqrt((node1.x - node2.x) * (node1.x - node2.x) + (node1.y - node2.y) * (node1.y - node2.y));
}

Stack<Point> ConvexHull(int n, double x[], double y[]) {
	Point* node = new Point[n];
	Point minNode(0, x[0], y[0]);
	for(int i = 0;i < n;++ i) {
		node[i] = Point(i, x[i], y[i]);
		if(y[i] - minNode.y < 0) {
			minNode = node[i];
		}
		else if((abs(y[i] - minNode.y) <= eps) && x[i] - minNode.x < 0) {
			minNode = node[i];
		}
	}
	
	Line* line = new Line[n - 1];
	int tot = 0;
	
	for(int i = 0;i < n;++ i) {
		if(minNode.num == i) continue;
		line[tot ++] = Line(minNode, node[i]);
	}
	
	
	
	std::sort(line, line + tot, cmp);
	
//	/*
//	²âÊÔ 
//	*/
//	for(int i = 0;i < tot;++ i) {
//		printf("(%lf, %lf)->(%lf, %lf), rate:%lf\n", line[i].a.x, line[i].a.y, line[i].b.x, line[i].b.y, line[i].theta);
//	} 

	Stack<Point> stack;
	stack.push(minNode);

	for(int i = 0;i < n - 1;++ i) {
		Point now = line[i].b;
		
		if(stack.size() == 1) {
			stack.push(now);
		}
		else {
			while(stack.size() >= 2) {				
				Point node2 = stack.top();
				stack.pop();
				Point node1 = stack.top();
				stack.push(node2);
				
				Point vec1 = vec(-1, node1, node2);
				Point vec2 = vec(-1, node2, now);
				double mul = cross(vec1, vec2);
				
				if(abs(mul) > eps && mul < 0) stack.pop();
				else break;
			}
			stack.push(now);			
		}
	}
	
	return stack;
}


int main() {
	freopen("data.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	double* x = new double[n];
	double* y = new double[n];
	for(int i = 0;i < n;++ i) {
		scanf("%lf %lf", &x[i], &y[i]);		
	}
	Stack<Point> stack = ConvexHull(n, x, y);
	
	double sum = 0;
	
	Point pre = stack.top();
	Point first = pre;
	stack.pop();
	while(!stack.empty()) {
		sum += distance(pre, stack.top());
		pre = stack.top();
		stack.pop();
	}
	sum += distance(pre, first);
	printf("%.2lf", sum);
	
	
	return 0;
}


