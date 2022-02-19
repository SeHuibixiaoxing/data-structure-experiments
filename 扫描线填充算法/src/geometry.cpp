#include "geometry.h"


const double eps = 1e-8;

int dcmp(double x) {
	if (fabs(x) < eps) {
		return 0;
	}
	else if (x < 0) {
		return -1;
	}
	else {
		return 1;
	}
}

double cross(const Point& s1, const Point& e1, const Point& s2, const Point& e2) {
	double x1 = e1.x - s1.x;
	double y1 = e1.y - s1.y;
	double x2 = e2.x - s2.x;
	double y2 = e2.y - s2.y;
	return x1 * y2 - y1 * x2;
}

double doubleDistance(const Point& a, const Point& b) {
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	return dx * dx + dy * dy;
}

double distance(const Point& a, const Point& b) {
	return sqrt(doubleDistance(a, b));
}

//判断三点是否共线
bool Collinear(const Point& p1, const Point& p2, const Point& p3) {
	Line l1(p1, p2), l2(p2, p3);
	return dcmp(l1.getK() - l2.getK()) == 0;
}

