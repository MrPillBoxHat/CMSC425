#pragma once

#include <Windows.h>
#include "Point2D.h"

class Rectangle2D
{
protected:
	Point2D origin;
	double width;
	double height;

	bool between(double p, double x, double length) const;
public:
	Rectangle2D(void);
	Rectangle2D(double x, double y, double w, double h);
	~Rectangle2D(void);

	Point2D getOrigin() const { return origin;}
	double getWidth() const { return width; }
	double getMaxX() const { return origin.getX() + width; }
	double getMaxY() const { return origin.getY() + height; }
	double getMinY() const { return origin.getY(); }
	double getMinX() const { return origin.getX(); }

	bool betweenX(double x) const { return between(x, origin.getX(), width); }

	bool intersects(const Point2D &point) const;
	bool intersects(const Rectangle2D &rect) const;
	bool operator < (const Rectangle2D &) const;
	bool operator == (const Rectangle2D &) const;
};

