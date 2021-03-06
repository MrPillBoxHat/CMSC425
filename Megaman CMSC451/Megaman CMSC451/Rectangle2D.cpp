#include "Rectangle2D.h"


Rectangle2D::Rectangle2D(void) {
	Rectangle2D(0, 0, 0 ,0);
}

Rectangle2D::Rectangle2D(double x, double y, double w, double h) {
	origin = Point2D(x, y);
	width = w;
	height = h;
}


Rectangle2D::~Rectangle2D(void)
{
}


bool Rectangle2D::intersects(const Point2D &point) const {
	return between(point.getX(), origin.getX(), width) && 
		   between(point.getY(), origin.getY(), height);
}

bool Rectangle2D::intersects(const Rectangle2D &rect) const {
	return getMinX() <= rect.getMaxX() &&
		   getMaxX() >= rect.getMinX() &&
		   getMinY() <= rect.getMaxY() &&
		   getMaxY() >= rect.getMinY();
}

bool Rectangle2D::between(double p, double x, double length) const {
	return x <= p && p <= (x + length);
}

bool Rectangle2D::operator <(const Rectangle2D & rec) const {
	Point2D diff = origin - rec.origin;

	if(diff.getX() == 0)
		return origin.getY() < rec.origin.getY();
	else if(diff.getY() == 0)
		return diff.getX() < 0;
	else
		return diff.getY() < 0;

}
bool Rectangle2D::operator== (const Rectangle2D & rec) const {
	return origin == rec.origin;
}
