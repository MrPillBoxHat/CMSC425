#pragma once

#include <stdlib.h>
#include <GL\glut.h>

#include "Rectangle2D.h"
#include "Texture.h"

class Box : public Rectangle2D
{
public:
	Box(int x, int y, UINT w, UINT h);
	Box(int x, int y, UINT w, UINT h, Texture * tex);
	~Box(void);

	void draw();
	void setColor(GLubyte r, GLubyte g, GLubyte b);
private:
	GLubyte clr[3];
	Texture * txtr;

	void simpleDraw();
	void textureDraw();
};

