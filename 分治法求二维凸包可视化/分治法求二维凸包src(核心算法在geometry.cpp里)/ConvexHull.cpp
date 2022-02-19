#include "ConvexHull.h"

void ConvexHull::copyPointSet(const std::vector<Point>& pointSet)
{
	this->point = pointSet;
	n = pointSet.size();
	now_rank = 0;
}

ConvexHull::ConvexHull()
{
	n = now_rank = 0;
	point.clear();
}

Point ConvexHull::get(const int& rank) const {
	return point[rank];
}

Point ConvexHull::getPre()
{
	return this->point[(this->now_rank - 1 + n) % n];
}

Point ConvexHull::getPre(int x)
{
	while (x > n) x -= n;
	return this->point[(this->now_rank - (x % n) + n) % n];
}

Point ConvexHull::getNext()
{
	return this->point[(this->now_rank + 1) % n];
}

Point ConvexHull::getNext(int x)
{
	return this->point[(this->now_rank + (x % n) + n) % n];
}

Point ConvexHull::getNow()
{
	return this->point[this->now_rank];
}

int ConvexHull::getNowRank()
{
	return this->now_rank;
}

int ConvexHull::getNextRank()
{
	return (this->now_rank + 1) % n;
}

int ConvexHull::getPreRank()
{
	return (this->now_rank - 1 + n) % n;
}

int ConvexHull::getNextRank(int x)
{
	return (this->now_rank + (x % n) + n) % n;
}

int ConvexHull::getPreRank(int x)
{
	return (this->now_rank - (x % n) + n) % n;
}

//void ConvexHull::insert(const Point& x) {
//
//}
//
//void ConvexHull::erase(const int& rank) {
//
//}

void ConvexHull::next() {
	this->now_rank = (this->now_rank + 1) % n;
}

void ConvexHull::next(const int& x) {
	this->now_rank = (this->now_rank + (x % n)) % n;
}

void ConvexHull::pre() {
	this->now_rank = (this->now_rank - 1 + n) % n;
}

void ConvexHull::pre(const int& x) {
	this->now_rank = (this->now_rank - (x % n) + n) % n;
}

void ConvexHull::adjust(const int& rank) {
	this->now_rank = rank;
}

int ConvexHull::size() {
	return n;
}

bool ConvexHull::empty() {
	return n == 0;
}
