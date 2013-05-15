#pragma once

#include <stdlib.h>
#include <GL\glut.h>

#include "Rectangle2D.h"
#include "Texture.h"

class Box : public Rectangle2D
{
public:
	Box(double x, double y, double w, double h);
	Box(double x, double y, double w, double h, Texture * tex);
	~Box(void);

	void draw();
	void setColor(GLubyte r, GLubyte g, GLubyte b);
private:
	GLubyte clr[3];
	Texture * txtr;

	void simpleDraw();
	void textureDraw();
};

