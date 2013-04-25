#pragma once
//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
//	File: World.h - Definitions for World object
//----------------------------------------------------------------------

#include <queue> // STL queue
#include "Player.h" // Player definitions
#include "Movement.h"
#include "RGBpixmap.h"

//----------------------------------------------------------------------
// World
//
// Our world is rather simple. It consists of a ground, a collection of
// snowmen, and a camera. We provide methods for constructing the world,
// for drawing the world, and updating the world. The update procedure
// involves moving the camera as long as the user is holding down either
// the up or down arrow keys.
//
// The coordinate system is set up so that the (x,y)-coordinate plane
// is the ground, and the z-axis is directed upwards. The y-axis points
// to the north and the x-axis points to the east.
//
// The values (x,y) are the current camera position. The values (lx, ly)
// point in the direction the camera is looking. The variables angle and
// deltaAngle control the camera's angle. The variable deltaMove
// indicates the amount of incremental motion for the camera with each
// redraw cycle. The variables isDragging and xDragStart are used to
// monitor the mouse when it drags (with the left button down).
//----------------------------------------------------------------------
class World {
private: // private data
	Player tommy; // tommy the terp
	GLint w, h;
	std::queue<Movement *> views;
	Movement * view;

 // private utility functions
	void drawBackground();
	void createLight();
	void changeCamera(); 
	void createLight(unsigned int light, GLfloat[], GLfloat[]);
public: // public interface
	World(); // constructor

	void init();
	void setAspectRatio(float ratio); // set the aspect ratio
	void setWH(GLint w, GLint h);
	void update(); // update (with each idle event)
	void draw(); // draw everything
	void processNormalKeys(unsigned char key, int xx, int yy);
	void releaseNormalKeys(unsigned char key, int xx, int yy);
	void pressSpecialKey(int key, int xx, int yy); // special key press
	void releaseSpecialKey(int key, int xx, int yy); // special key release
	void mouseMove(int xx, int yy); // mouse dragged
	void mouseButton(int button, int state, int xx, int yy); // mouse button
};

