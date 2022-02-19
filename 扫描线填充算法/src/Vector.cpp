#include "Vector.h"

Vector::Vector(const double& x1, const double& y1, const double& x2, const double& y2)
{
	s = Point(x1, y1);
	e = Point(x2, y2);
}