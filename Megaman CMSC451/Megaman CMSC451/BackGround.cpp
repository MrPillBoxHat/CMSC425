#include "BackGround.h"

#include <string>
#include <iostream>

using namespace std;

BackGround::BackGround(void): viewWidth(1000), viewHeight(650)
{
}


BackGround::~BackGround(void)
{
}

void BackGround::draw(GLint cmX) 
{
	// background view
	drawView(cmX);
	drawGround();
}

void BackGround::drawGround() 
{
	for(Box * bx : ground) // draw each box
	{
		glColor3f(1, 1, 1);
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

void BackGround::drawView(GLint cmX)
{
	glColor3f(1, 1, 1);
	/*const UINT Y = 100;
	const UINT H = height - viewHeight;
	const UINT W = width/5;

	for(UINT x = 0; x < width; x += W) 
	{
		Box b(x, Y, W, H, bg);
		b.draw();
	}
	*/
	const UINT Y = 100;
	const UINT H = height - viewHeight;
	const UINT W = viewWidth;
	Box b(cmX, Y, W, H, bg);
	b.draw();
}
Rectangle2D * BackGround::getBelow(float x, float y)
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

bool BackGround::canMove(float x, float y)
{
	if(x < 0 || x > width) return false; // out of boundary

	const Point2D pnt = Point2D(x, y);

	for(Box * bx : ground)
		if( bx->intersects(pnt) )
			return false;

	return true;
}

void BackGround::initGround()
{
	// load textures for background
	initTextures(); 
	const UINT H = 100;

	Box * bx = new Box(0, 0, 400, H, grdTxt); // yellow box
	ground.push_back(bx);

	bx = new Box(400, 0, 400, H, grdTxt);	// red box
	ground.push_back(bx);

	bx = new Box(800, 0, 400, H, grdTxt); // green box
	ground.push_back(bx);

	bx = new Box(1200, 0, 100, H/4); // pit
	ground.push_back(bx);

	bx = new Box(1300, 0, 300, H, grdTxt); // space, then another block
	ground.push_back(bx);

	for(UINT x = 1600; x < width; x += 400) 
	{
		bx = new Box(x, 0, 400, H, grdTxt);  // rest of the floor
		ground.push_back(bx);
	}


	// small box on top
	bx = new Box(500, H, 200, H/5);
	bx->setColor(50, 50, 150);
	ground.push_back(bx);

		// small box on top
	bx = new Box(1400, H, 200, H/5);
	bx->setColor(150, 50, 150);
	ground.push_back(bx);

	bx = new Box(3400, H, width-3400, height - viewHeight, bossTxt);
	ground.push_back(bx);

	// main background
	view = new Box(0, H, width/10, height - viewHeight, bg);
}

void BackGround::initTextures()
{
	grdTxt = new Texture("Sprites/Background/ground.png");

	bossTxt = new Texture("Sprites/Misc/mmx5_dynamo_stage_bg_c.png");
	// set edges
	bossTxt->setBoundary(.5, .1, 1, 1);

	// background
	bg = new Texture("Sprites/Background/sky.png");
	bg->setBoundary(.05, .3, 1, 1);
}