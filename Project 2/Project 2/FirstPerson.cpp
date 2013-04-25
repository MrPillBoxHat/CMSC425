#include "stdafx.h"
#include "FirstPerson.h"
#define PI 3.141592


FirstPerson::FirstPerson(Player * p1) : Movement(p1), RAD(1)
{
	aspectRatio = 1; // default aspect ratio (will be changed)

	angle = PI/2; // angle of rotation for the camera direction
	zAng = 0.0;
	angD = zD = 0.0;

	// Camera position
	x = cos(angle)*RAD; 
	y = sin(angle)*RAD; z = 1; // initially 5 units south of origin

	deltaMoveY = 0.0; // initially camera doesn't move
	deltaMoveX = 0.0;
	deltaMove = 0.0;

	// Camera direction
	lx = 0.0; ly = 1.0, lz = 1; // camera points initially
	deltaAngle = 0.0; // additional angle change when dragging

	// Mouse drag control
	isDragging = false; // true when dragging
	xDragStart = 0; // records the x-coordinate when dragging starts
}


FirstPerson::~FirstPerson(void)
{
}

void FirstPerson::update()
{
	if (isDragging) { // update camera position
		//x += deltaMoveY * lx * 0.1;
		//y += deltaMoveY * ly * 0.1;
		//angleCamera(x, y);
		angle += (PI/180.0)*angD;
		calcZAngle();

		x = cos(angle)*RAD; 
		y = sin(angle)*RAD;
	}
	
	tommy->setAngle( (angle - PI/2) ); // gotta change to degrees
	if(deltaMove) {
		tommy->moveX(-deltaMove * cos(angle + PI));
		tommy->moveY(-deltaMove * sin(angle + PI));
	}
}

void FirstPerson::calcZAngle()
{
	const double LIM = PI / 3.0;

	if(zD > 0)
		zAng += (zAng >= LIM) ? 0 :(PI/180.0)*zD;
	else if(zD < 0)
		zAng += (zAng <= -LIM) ? 0 :(PI/180.0)*zD;
}

void FirstPerson::setUpCamera()
{
	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	const GLdouble ex = tommy->X() + this->x;
	const GLdouble ey = tommy->Y() +  this->y;

	const GLdouble cx = tommy->X() + cos(angle)*RAD*2;
	const GLdouble cy = tommy->Y() + sin(angle)*RAD*2;
	const GLdouble cz = lz + sin(zAng);
	gluLookAt(
			ex,  ey,   z,
			cx,  cy,   cz,
			0.0, 0.0,  1.0);

	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, aspectRatio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}

void FirstPerson::processNormalKeys(unsigned char key, int x, int y)
{
	const int ESC = 27; // escape key (for exit)
	const double DELTA = .001;


	switch(tolower(key)) {
	case ESC:
	case 'q':
		exit(0);
		break;
	case UP:
		deltaMove = DELTA; 
		break;
	case DOWN:
		deltaMove = 0; 
		break;
	case LEFT:
		angD = 0.05;
		isDragging = true; // start dragging
		break;
	case RIGHT:
		angD = -0.05;
		isDragging = true; // start dragging
		break;
	}
}

void FirstPerson::releaseNormalKeys(unsigned char key, int x, int y)
{
	switch(tolower(key)) {
	case UP:
	case DOWN:
		deltaMove = 0; 
		break;
	case LEFT:
	case RIGHT:
		isDragging = false;
		break;
	}
}

void FirstPerson::angleCamera()
{
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (tommy->X() - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
}

void FirstPerson::mouseMove(int x, int y)
{
	if(isDragging) {
		int sign = (x > w/2.0) ? -1 : 1;
		angD = 0.05 * sign;

		sign = (y > h/2.0) ? -1 : 1;
		zD = 0.015 * sign;
	}
}

void FirstPerson::mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) {
		isDragging = (state == GLUT_DOWN);
		/*
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = true; // start dragging
		}
		else  { // (state = GLUT_UP)
			angle += deltaAngle; // update camera turning angle
			isDragging = false; // no longer dragging
		}
		*/
	}
}
