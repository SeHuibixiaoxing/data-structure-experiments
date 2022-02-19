#include "Point.h"
#include "geometry.h"

Point::Point() {
	this->x = this->y = 0;
}

bool Point::operator==(const Point& p) const
{
	if (dcmp(p.x - this->x) == 0 && dcmp(p.y - this->y) == 0) {
		return true;
	}
	return false;
}


