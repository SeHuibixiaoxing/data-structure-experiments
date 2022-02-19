#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "geometry.h"


int main() {
	freopen("D:\\材料\\学堂课程资料\\大二上\\数据结构\\作业\\07 二维凸包(分治法)\\分治法求二维凸包\\data.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	std::vector<Point> point;
	for (int i = 0; i < n; ++i) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		point.push_back(Point(x, y));
	}
	ConvexHull ans = GetConvexHull(point);
	double sum = 0;
	ans.adjust(0);
	for (; ans.getNextRank() != 0; ans.next()) {
		sum += distance(ans.getNow(), ans.getNext());
	}
	sum += distance(ans.getNow(), ans.getNext());

	printf("%.2lf", sum);
}

