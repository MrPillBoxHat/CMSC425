#include "BackGround.h"

#include <string>
#include <iostream>

using namespace std;

BackGround::BackGround(void): viewWidth(1000), viewHeight(650)
{
	x1 = 0.0;
}


BackGround::~BackGround(void)
{
	for(Box *bx : groundTxtr)
		delete bx;
	for(Rectangle2D *r : ground)
		delete r;

	delete view;
	delete bg;
	delete grdTxt;
	delete bossTxt;
	delete pillarTxt;

}

void BackGround::draw(GLint cmX) 
{
	// background view
	drawView(cmX);
	drawGround();
}

void BackGround::drawGround() 
{
	for(Box * bx : groundTxtr) // draw each box
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
	const UINT H = viewHeight - Y;
	const UINT W = viewWidth;
	Box b(cmX, Y, W, H, bg);
	b.draw();
}
Rectangle2D * BackGround::getBelow(double x, double y)
{
	Rectangle2D * ret = nullptr;
	for(Rectangle2D * bx : ground)
	{
		if(bx->betweenX(x)) 
			if(ret == nullptr || bx->getMaxY() > ret->getMaxY())
				ret = bx;
	}
	return ret;
}


bool BackGround::canMove(double x1, double y1, double x2, double y2) const
{
	if((x1 < this->x1 || x1 >= width) || (x2 < this->x1 || x2 >= width)) 
		return false; // out of boundary

	const Rectangle2D rect(x1, y1, y2-y1, x2-x1);

	for(Rectangle2D * bx : ground)
		if(bx->intersects(rect))
			return false;

	return true;
}

bool BackGround::canMove(double x, double y) const
{
	if((x < this->x1 || x >= width-25)) 
		return false; // out of boundary

	const Point2D pt(x, y);

	for(Rectangle2D * bx : ground)
		if(bx->intersects(pt))
			return false;

	return true;
}

void BackGround::initGround()
{
	// load textures for background
	initTextures(); 
	const UINT Tx_H = 100; // texture height
	const UINT mm_h = 72; // megaman height

	addBox(0, 400, Tx_H, grdTxt, mm_h);

	addBox(400, 400, Tx_H, grdTxt, mm_h);

	addBox(800, 400, Tx_H, grdTxt, mm_h);

	addBox(1200, 100, Tx_H/4, nullptr, Tx_H/5);

	addBox(1300, 300, Tx_H, grdTxt, mm_h);

	for(UINT x = 1600; x < width; x += 400) 
	{
		addBox(x, 400, Tx_H, grdTxt, mm_h);
	}


	/*
	// small box on top
	bx = new Box(500, H, 200, H/5);
	bx->setColor(50, 50, 150);
	ground.push_back(bx);

		// small box on top
	bx = new Box(1400, H, 200, H/5);
	bx->setColor(150, 50, 150);
	ground.push_back(bx);
	*/

	//bx = new Box(3200, 50, width-3200, viewHeight-50, bossTxt);
	//ground.push_back(bx);

	// main background
	view = new Box(0, Tx_H, width/10, height - viewHeight, bg);

	//two pillars
	addBox(500, 100, 250, pillarTxt, 225, 60);
	for(int x1 = 700; x1 <= 900; x1 += 100)
		addBox(x1, 100, 250, pillarTxt, 225, 60);
	addBox(1000, 100, 150, pillarTxt, 125, 60);

	// stairs
	for(int x1 = 1500, h = 150; x1 <= 2200; x1 += 100, h += 50)
		addBox(x1, 100, h, pillarTxt, h-25, 60);
}

void BackGround::addBox(double x1, double w, double txtH, Texture * txt, double rlH, double y1)
{
	Box * bx = nullptr;
	if(txt != nullptr)
		bx = new Box(x1, y1, w, txtH, txt);
	else
		bx = new Box(x1, y1, w, txtH);

	groundTxtr.push_back(bx);

	// "real" ground
	ground.push_back( new Rectangle2D(x1, y1, w, rlH) );
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

	pillarTxt = new Texture("Sprites/Background/pillar1.png");
}