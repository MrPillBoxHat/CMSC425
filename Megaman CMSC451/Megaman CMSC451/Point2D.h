#pragma once
class Point2D
{
public:
	Point2D(void);
	Point2D(int x, int y);
	~Point2D(void);
private:
	int x;
	int y;
public:
	bool operator ==(const Point2D &p2) const;
	Point2D operator +(Point2D &p2);
	Point2D operator -(const Point2D &p2) const;

	int getX() const { return x;}
	int getY() const { return y;}
};

