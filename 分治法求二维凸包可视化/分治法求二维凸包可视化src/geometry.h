#pragma once
#include "Point.h"
#include "Line.h"
#include "Vector.h"
#include "ConvexHull.h"
#include "draw.h"
#include <graphics.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2);	//计算直线s1e1与直线s2e2的叉积
double doubleDistance(const Point& a, const Point& b);					//计算点a到点b距离的平方
double distance(const Point& a, const Point& b);						//计算点a到点b距离
int dcmp(double x);
double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2);
double doubleDistance(const Point& a, const Point& b);
double distance(const Point& a, const Point& b);
bool Collinear(const Point& p1, const Point& p2, const Point& p3);
std::vector<int> TangentPointRank(const Point& point, ConvexHull& hull);
std::vector<Point> TangentPoint(const Point& point, ConvexHull& hull);
ConvexHull MergeSeparateConvexHull(ConvexHull& hull1_tmp, ConvexHull& hull2_tmp, std::vector<Point>& drawPointSet, std::vector<Point>& drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet);
ConvexHull GetConvexHull(std::vector<Point>& pointSet, int l, int r, std::vector<Point>& drawPointSet, std::vector<Point>& drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet, int milliseconds);
ConvexHull GetConvexHull(const std::vector<Point>& pointSet, std::vector<Point>& drawPointSet, std::vector<Point>& drawKeyPointSet, std::vector<std::pair<Point, Point>>& drawLineSet, int milliseconds);


