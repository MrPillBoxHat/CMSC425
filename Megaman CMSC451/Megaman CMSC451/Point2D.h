#pragma once
class Point2D
{
public:
	Point2D(void);
	Point2D(double x, double y);
	~Point2D(void);
private:
	double x;
	double y;
public:
	bool operator ==(const Point2D &p2) const;
	Point2D operator +(Point2D &p2);
	Point2D operator -(const Point2D &p2) const;

	double getX() const { return x;}
	double getY() const { return y;}
};

