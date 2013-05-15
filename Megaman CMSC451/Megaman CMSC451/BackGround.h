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
	void setStart(GLdouble x) { this->x1 = x; }
	// Create the boxes for the ground
	void initGround();
	// retrieve the rectangle below this point
	Rectangle2D * getBelow(GLdouble x, GLdouble y);
	bool canMove(GLdouble x, GLdouble y) const;
	bool canMove(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) const;

	const GLdouble viewWidth, viewHeight;

private:
	GLdouble width, height;
	GLdouble x1;

	std::vector<Box *> groundTxtr;
	std::vector<Rectangle2D *> ground;

	Box * view;
	Texture * bg;

	Texture * grdTxt;
	Texture * bossTxt, * pillarTxt;

	void initTextures();
	void drawGround();
	void drawView(GLint cmX);
	void drawTop();
	void addBox(GLdouble x1, GLdouble w, GLdouble h, Texture * txt, GLdouble rlH, GLdouble y1=0);
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