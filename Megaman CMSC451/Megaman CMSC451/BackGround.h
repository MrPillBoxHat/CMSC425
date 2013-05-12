#pragma once

#include <stdlib.h>
#include <GL\glut.h>
#include <vector>

#include "Rectangle2D.h"
#include "Box.h"

class BackGround
{
public:
	BackGround(void);
	~BackGround(void);

	void draw();
	void setBoundary(GLdouble w, GLdouble h) { width = w; height = h;}
	// Create the boxes for the ground
	void initGround();
	// retrieve the rectangle below this point
	Rectangle2D & getBelow(GLint x, GLint y);
	bool canMove(GLint x, GLint y);

	const GLdouble viewWidth, viewHeight;

private:
	GLdouble width, height;	
	std::vector<Box *> ground;

	void drawGround();
	void drawTop();
};

/*
class Box
{
	Color * color;
};

class Color 
{
	GLubyte c[3];

	Color(GLubyte r, GLubyte g, GLubyte b)
	{
		c[0] = r; c[1] = g; c[2] = b;
	}
};
*/