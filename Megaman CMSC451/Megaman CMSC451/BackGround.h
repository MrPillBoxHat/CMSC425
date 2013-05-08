#pragma once

#include <stdlib.h>
#include <GL\glut.h>

class BackGround
{
public:
	BackGround(void);
	~BackGround(void);

	void draw();
	void setBoundary(GLdouble w, GLdouble h) { width = w; height = h;}

	const GLdouble viewWidth, viewHeight;

private:
	GLdouble width, height;	

	void drawGround();
};

