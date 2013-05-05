#include "BackGround.h"

#include <GL\glut.h>

BackGround::BackGround(void)
{
}


BackGround::~BackGround(void)
{
}

void BackGround::draw() 
{
	//yellow block
	glColor3ub(255, 255, 0);
    glRectf(0.0f,0.0f, 400.0f, 100.0f);
	// red block
	glColor3ub(255, 0, 0);
    glRectf(400.0f,0.0f, 800.0f, 100.0f);
	// green block
	glColor3ub(0, 255, 0);
    glRectf(800.0f,0.0f, 1200.0f, 100.0f);

	// space, then another block
	glColor3ub(0, 150, 100);
    glRectf(1250.0f,0.0f, 1650.0f, 100.0f);
}