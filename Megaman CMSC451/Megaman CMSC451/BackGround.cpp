#include "BackGround.h"

#include <string>

using namespace std;

BackGround::BackGround(void): viewWidth(800), viewHeight(400)
{
}


BackGround::~BackGround(void)
{
}

void BackGround::draw() 
{
	drawGround();
}

void BackGround::drawGround() 
{
	//yellow block
	glColor4f(255, 255, 0, 1);
    glRectf(0.0f,0.0f, 400.0f, 100.0f);
	// red block
	glColor4f(255, 0, 0, 1);
    glRectf(400.0f,0.0f, 800.0f, 100.0f);
	// green block
	glColor4f(0, 255, 0, 1);
    glRectf(800.0f,0.0f, 1200.0f, 100.0f);

	// space, then another block
	glColor4f(0, 150, 100, 1);
    glRectf(1250.0f,0.0f, 1650.0f, 100.0f);

	// drawing rest of the floor
	glColor3ub(150, 150, 150);
    glRectf(1650.0f,0.0f, width, 100.0f);

	// start message
	glColor3f(0, 1, 0);
	glRasterPos2d(5, 350);
	string start = "Let the games begin!";
	for(char c : start)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	// end message
	glColor3f(0, 1, 0);
	glRasterPos2d(width-100, 350);
	string str = "The End";
	for(char c : str)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}