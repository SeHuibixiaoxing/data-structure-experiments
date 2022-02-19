#pragma once
#include "Point.h"
#include "Line.h"
#include "Vector.h"
#include "ConvexHull.h"

double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2);	//����ֱ��s1e1��ֱ��s2e2�Ĳ��
double doubleDistance(const Point& a, const Point& b);					//�����a����b�����ƽ��
double distance(const Point& a, const Point& b);						//�����a����b����
int dcmp(double x);
double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2);
double doubleDistance(const Point& a, const Point& b);
double distance(const Point& a, const Point& b);
bool Collinear(const Point& p1, const Point& p2, const Point& p3);
std::vector<int> TangentPointRank(const Point& point, ConvexHull& hull);
std::vector<Point> TangentPoint(const Point& point, ConvexHull& hull);
ConvexHull MergeSeparateConvexHull(ConvexHull& hull1, ConvexHull& hull2);
ConvexHull GetConvexHull(std::vector<Point>& pointSet, int l, int r);
ConvexHull GetConvexHull(const std::vector<Point>& pointSet);



