#pragma once

#include <stdlib.h>
#include <GL\glut.h>
#include <vector>

#include "Rectangle2D.h"
#include "Box.h"
#include "Texture.h"

class BackGround
{
public:
	BackGround(void);
	~BackGround(void);

	void draw(GLint cmX);
	void setBoundary(GLdouble w, GLdouble h) { width = w; height = h;}
	// Create the boxes for the ground
	void initGround();
	// retrieve the rectangle below this point
	Rectangle2D * getBelow(float x, float y);
	bool canMove(float x, float y);

	const GLdouble viewWidth, viewHeight;

private:
	GLdouble width, height;	
	std::vector<Box *> ground;
	Box * view;
	Texture * bg;

	Texture * grdTxt;
	Texture * bossTxt;

	void initTextures();
	void drawGround();
	void drawView(GLint cmX);
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