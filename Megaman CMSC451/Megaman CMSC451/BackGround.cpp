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
	glColor3ub(254, 255, 0);
    glRectf(0.0f,0.0f, 400.0f, 100.0f);
}