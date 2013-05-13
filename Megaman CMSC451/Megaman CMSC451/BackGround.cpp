#include "BackGround.h"

#include <string>
#include <iostream>

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
	for(Box * bx : ground) // draw each box
	{
		bx->draw();
	}

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

Rectangle2D * BackGround::getBelow(GLint x, GLint y)
{
	Box * ret = nullptr;

	for(Box * bx : ground)
	{
		if(bx->betweenX(x) && y >= bx->getMaxY() )
			if(ret == nullptr || bx->getMaxY() > ret->getMaxY())
				ret = bx;
	}

	return ret;
}

bool BackGround::canMove(GLint x, GLint y)
{
	const Point2D pnt = Point2D(x, y);

	for(Box * bx : ground)
		if( bx->intersects(pnt) )
			return false;

	return true;
}

void BackGround::initGround()
{
	const UINT H = 100;

	Box * bx = new Box(0, 0, 400, H); // yellow box
	bx->setColor(255, 255, 0);
	ground.push_back(bx);

	bx = new Box(400, 0, 400, H);	// red box
	bx->setColor(255, 0, 0);
	ground.push_back(bx);

	bx = new Box(800, 0, 400, H); // green box
	bx->setColor(0, 255, 0);
	ground.push_back(bx);

	bx = new Box(1200, 0, 100, H/4); // pit
	ground.push_back(bx);

	bx = new Box(1300, 0, 400, H); // space, then another block
	bx->setColor(0, 150, 100);
	ground.push_back(bx);

	bx = new Box(1700, 0, width - 1650 , H);  // rest of the floor
	bx->setColor(150, 150, 150);
	ground.push_back(bx);

	// small box on top
	bx = new Box(500, H, 200, H/5);
	bx->setColor(50, 50, 150);
	ground.push_back(bx);

		// small box on top
	bx = new Box(1400, H, 200, H/5);
	bx->setColor(150, 50, 150);
	ground.push_back(bx);
}