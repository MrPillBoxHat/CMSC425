#pragma once

#include <stdlib.h>
#include <GL\glut.h>

#include "Rectangle2D.h"

class Box : public Rectangle2D
{
public:
	Box(int x, int y, UINT w, UINT h);
	Box(int x, int y, UINT w, UINT h, GLint tex);
	~Box(void);

	void draw();
	void setColor(GLubyte r, GLubyte g, GLubyte b);
private:
	GLubyte clr[3];
	GLint txtr;

	void simpleDraw();
	void textureDraw();
};

