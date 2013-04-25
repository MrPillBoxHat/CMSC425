#include "stdafx.h"
#include "ThirdPerson.h"

#define PI 3.141592

ThirdPerson::ThirdPerson(Player * p1) : Movement(p1), RAD(10.0)
{
	aspectRatio = 1; // default aspect ratio (will be changed)

	angle = -PI/2; // angle of rotation for the camera direction
	// Camera position
	x = cos(angle)*RAD; 
	y = sin(angle)*RAD; z = 10.0; // initially 5 units south of origin

	deltaMoveY = 0.0; // initially camera doesn't move
	deltaMoveX = 0.0;
	deltaMove = 0.0;

	// Camera direction
	lx = 0.0; ly = 1.0, lz = -0.5; // camera points initially
	deltaAngle = 0.0; // additional angle change when dragging

	// Mouse drag control
	isDragging = false; // true when dragging
	xDragStart = 0; // records the x-coordinate when dragging starts
}


ThirdPerson::~ThirdPerson(void)
{
}

void ThirdPerson::update()
{
	if (isDragging) { // update camera position
		//x += deltaMoveY * lx * 0.1;
		//y += deltaMoveY * ly * 0.1;
		//angleCamera(x, y);
		angle += (PI/180.0)*angD;
		std::cout << "angle " << angle << std::endl;
		x = cos(angle)*RAD; 
		y = sin(angle)*RAD;
	}
	
	tommy->setAngle( (angle - PI/2) ); // gotta change to degrees
	if(deltaMove) {
		tommy->moveX(deltaMove * cos(angle + PI));
		tommy->moveY(deltaMove * sin(angle + PI));
	}
}

void ThirdPerson::setUpCamera()
{
	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	const double ey = tommy->Y() + this->y;
	const double ex = tommy->X() + this->x;
	gluLookAt(
			ex,      ey,      z,
			 tommy->X(),  tommy->Y(), 1,
			0.0,    0.0,    1.0);

	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, aspectRatio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}

void ThirdPerson::processNormalKeys(unsigned char key, int x, int y)
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

void ThirdPerson::releaseNormalKeys(unsigned char key, int x, int y)
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

void ThirdPerson::angleCamera()
{
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (tommy->X() - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
}

void ThirdPerson::mouseMove(int x, int y)
{
	
}

void ThirdPerson::mouseButton(int button, int state, int x, int y) 
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
