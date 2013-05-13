#pragma once

#include <string>
#include <GL/glut.h>

class Point
{
public:
	GLdouble x, y;

	Point(GLdouble x, GLdouble y) { this->x = x; this->y = y;}
	Point() { this->x = this->y = 0; }
};


class Texture
{
public:
	Texture(std::string fileName);
	~Texture(void);

	GLuint getId() const {return id;}
	void topLeft() const { glTexCoord2d(tL.x, tL.y);}
	void topRight() const { glTexCoord2d(tR.x, tR.y);}
	void bottLeft() const { glTexCoord2d(bL.x, bL.y);}
	void bottRight() const { glTexCoord2d(bR.x, bR.y);}

	void setTopLeft(GLdouble x, GLdouble y) { tL = Point(x, y);}
	void setTopRight(GLdouble x, GLdouble y) { tR = Point(x, y);}
	void setBottLeft(GLdouble x, GLdouble y) { bL = Point(x, y);}
	void setBottRight(GLdouble x, GLdouble y) { bR = Point(x, y);}
	void setBoundary(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);

private:
	GLuint id;
	// points
	Point tL, tR, bL, bR;
};


