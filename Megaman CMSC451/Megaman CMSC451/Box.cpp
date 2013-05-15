#include "Box.h"

#include <iostream>

Box::Box(double x, double y, double w, double h) : Rectangle2D(x, y, w , h)
{
	clr[0] = 235;
	clr[1] = 100;
	clr[2] = 100;
	txtr = nullptr;
}

Box::Box(double x, double y, double w, double h, Texture * texture) : Rectangle2D(x, y, w, h)
{
	txtr = texture;

	clr[0] = clr[1] = clr[2] = 255;
}

Box::~Box(void)
{
}

void Box::setColor(GLubyte r, GLubyte g, GLubyte b)
{
	clr[0] = r;
	clr[1] = g;
	clr[2] = b;
}

void Box::draw() 
{
	if(txtr != nullptr)
		textureDraw();
	else
		simpleDraw();
}

void Box::simpleDraw()
{
	glColor3ubv(clr);
	glRecti(origin.getX(), origin.getY(), getMaxX(), getMaxY()); 
}

void Box::textureDraw()
{
	glBindTexture(GL_TEXTURE_2D, txtr->getId()); // bind

	glBegin(GL_POLYGON);
		//real coord
		txtr->bottLeft();    glVertex2d(getMinX(), getMinY());
		txtr->bottRight();   glVertex2d(getMaxX(), getMinY());
		txtr->topRight();    glVertex2d(getMaxX(), getMaxY());
		txtr->topLeft();     glVertex2d(getMinX(), getMaxY());
	glEnd();
}