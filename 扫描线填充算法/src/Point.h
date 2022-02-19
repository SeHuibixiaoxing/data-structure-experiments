#pragma once
class Point {
public:
	double x, y;
	Point(const double& x, const double& y) :x(x), y(y) {}
	Point();

	bool operator ==(const Point& p) const;
};
