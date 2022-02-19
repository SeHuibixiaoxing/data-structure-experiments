#include "Line.h"
#include <cmath>
#include <cstdio>


Line::Line(const Point& a, const Point& b) {
	vec = Vector(a, b);
	this->angle = atan2(b.y - a.y, b.x - a.x);
	this->k = tan(angle);
	this->b = b.y - b.x * k;
	printf("%lf\n", this->k);
}

Line::Line(const double& k, const double& b)
{
	this->k = k;
	this->b = b;
	this->angle = atan(k);
	this->vec = Vector(1, k + b, 0, b);
}

Line::Line(const Vector& vec) {
	new (this)Line(vec.s, vec.e);
}

Line::Line()
{
	k = b = angle = 0;
}

double Line::getY(const double& x) {
	return this->k * x + this->b;
}

double Line::getX(const double& y) {
	return (y - this->b) / this->k;
}

double Line::getK() {
	return this->k;
}

double Line::getB() {
	return this->b;
}

void Line::copy(Line& line) {
	this->k = line.k;
	this->b = line.b;
	this->angle = line.angle;
	this->vec = line.vec;
}
