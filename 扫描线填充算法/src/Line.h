#pragma once

#include "Point.h"
#include "Vector.h"

class Line
{
private:
	double k, b, angle;
	Vector vec;

public:
	Line(const Point& a, const Point& b);
	Line(const double& k, const double& b);
	Line(const Vector& vec);
	Line();

	double getY(const double& x);
	double getX(const double& y);
	double getK();
	double getB();
	void copy(Line& line);
};
