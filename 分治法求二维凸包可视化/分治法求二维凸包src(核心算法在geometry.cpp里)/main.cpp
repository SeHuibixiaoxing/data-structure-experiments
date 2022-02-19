#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "geometry.h"


int main() {
	freopen("D:\\����\\ѧ�ÿγ�����\\�����\\���ݽṹ\\��ҵ\\07 ��ά͹��(���η�)\\���η����ά͹��\\data.txt", "r", stdin);
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

