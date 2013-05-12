#include "Point2D.h"


Point2D::Point2D(void)
{
	x = 0;
	y = 0;
}

Point2D::Point2D(int x, int y) {
	this->x = x;
	this->y = y;
}

Point2D::~Point2D(void) {
}


bool Point2D::operator ==(const Point2D &p2) const {
	return (x == p2.x) && (y == p2.y);
}

Point2D Point2D::operator +(Point2D &p2) {
	return Point2D(x + p2.x, y + p2.y);
}


Point2D Point2D::operator -(const Point2D &p2) const {
	return Point2D(x - p2.x, y - p2.y);
}
