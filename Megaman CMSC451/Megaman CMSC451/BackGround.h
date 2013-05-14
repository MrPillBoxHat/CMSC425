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
	Rectangle2D * getBelow(GLint x, GLint y);
	bool canMove(GLint x, GLint y) const;
	bool canMove(GLint x1, GLint y1, GLint x2, GLint y2) const;

	const GLdouble viewWidth, viewHeight;

private:
	GLdouble width, height;	
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
	void addBox(GLint x1, GLuint w, GLuint h, Texture * txt, GLuint rlH, GLint y1=0);
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