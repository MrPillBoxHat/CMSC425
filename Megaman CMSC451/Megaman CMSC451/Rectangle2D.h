#pragma once

#include <Windows.h>
#include "Point2D.h"

class Rectangle2D
{
protected:
	Point2D origin;
	UINT width;
	UINT height;

	bool between(int p, int x, int length) const;
public:
	Rectangle2D(void);
	Rectangle2D(int x, int y, UINT w, UINT h);
	~Rectangle2D(void);

	Point2D getOrigin() const { return origin;}
	UINT getWidth() const { return width; }
	int getMaxX() const { return origin.getX() + width; }
	int getMaxY() const { return origin.getY() + height; }
	int getMinY() const { return origin.getY(); }
	int getMinX() const { return origin.getX(); }

	bool betweenX(int x) const { return between(x, origin.getX(), width); }

	bool intersects(const Point2D &point) const;
	bool intersects(const Rectangle2D &rect) const;
	bool operator < (const Rectangle2D &) const;
	bool operator == (const Rectangle2D &) const;
};

