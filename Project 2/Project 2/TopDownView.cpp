#include "stdafx.h"
#include "TopDownView.h"

#define PI 3.141592

TopDownView::TopDownView(Player * p1) : Movement(p1)
{
	aspectRatio = 1; // default aspect ratio (will be changed)

	// Camera position
	x = 0.0; y = 22.0; z = 20.0; // initially 5 units south of origin
	deltaMoveY = 0.0; // initially camera doesn't move
	deltaMoveX = 0.0;

	// Camera direction
	lx = 0.0; ly = 1.0, lz = -1.0; // camera points initially
	angle = 0.0; // angle of rotation for the camera direction
	deltaAngle = 0.0; // additional angle change when dragging

	// Mouse drag control
	isDragging = false; // true when dragging
	xDragStart = 0; // records the x-coordinate when dragging starts

	p1->setPos(0,0);
}


TopDownView::~TopDownView(void)
{
}

void TopDownView::update()
{
	/*
	if (deltaMoveY) { // update camera position
		x += deltaMoveY * lx * 0.1;
		y += deltaMoveY * ly * 0.1;
	}
	*/

	if(deltaMoveY) {
		tommy->setAngle( getAngle(getDir(false, deltaMoveY)) );
		tommy->moveY(deltaMoveY);
	}

	if(deltaMoveX) {
		tommy->setAngle( getAngle(getDir(true, deltaMoveX)) );
		tommy->moveX(deltaMoveX);
	}
}

void TopDownView::setUpCamera()
{
	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	const GLdouble t = tommy->Y()-y; 
	gluLookAt(
			tommy->X(),    t,      z,
			tommy->X() + lx, t +ly, z + lz,
			0.0,    0.0,    1.0);

	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, aspectRatio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}

void TopDownView::processNormalKeys(unsigned char key, int x, int y)
{
	const int ESC = 27; // escape key (for exit)
	const double DELTA = .001;


	switch(tolower(key)) {
	case ESC:
	case 'q':
		exit(0);
		break;
	case UP:
		deltaMoveY = DELTA; 
		break;
	case DOWN:
		deltaMoveY = -DELTA; 
		break;
	case LEFT:
		deltaMoveX = -DELTA;
		break;
	case RIGHT:
		deltaMoveX = DELTA;
		break;
	}
}

void TopDownView::releaseNormalKeys(unsigned char key, int x, int y)
{
	switch(tolower(key)) {
	case UP:
	case DOWN:
		deltaMoveY = 0; 
		break;
	case LEFT:
	case RIGHT:
		deltaMoveX = 0;
		break;
	}
}

void TopDownView::mouseMove(int x, int y)
{
	/*
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
	*/
}

void TopDownView::mouseButton(int button, int state, int x, int y) 
{
	/*
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = true; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { // (state = GLUT_UP)
			angle += deltaAngle; // update camera turning angle
			isDragging = false; // no longer dragging
		}
	}
	*/
}

unsigned char TopDownView::getDir(bool x, GLdouble delta)
{
	if(x) {
		if(delta > 0)
			dir = R;
		else if(delta < 0)
			dir = L;
	} else {
		if(delta > 0)
			dir = U;
		else if(delta < 0)
			dir = D;
	}

	return dir;
}

GLdouble TopDownView::getAngle(unsigned char dir) {
	double ang = 0.0;

	switch(dir) {
	case R:
		ang = PI/2;
		break;
	case L:
		ang = -PI/2;
		break;
	case D:
		ang = 0.0;
		break;
	case U:
		ang = PI;
		break;
	}

	return ang;
}