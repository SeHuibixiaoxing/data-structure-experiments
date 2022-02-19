#pragma once

#include "Point.h"

class Vector
{
public:
	Point s, e;
	Vector(const Point& s, const Point& e) :s(s), e(s){}
	Vector(const double& x1, const double& y1, const double& x2, const double& y2);
	Vector() {}
};

