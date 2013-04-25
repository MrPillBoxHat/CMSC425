// Project 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//----------------------------------------------------------------------
// Global variables
//----------------------------------------------------------------------

World theWorld; // the world

//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels.
//----------------------------------------------------------------------
void changeSize(int w, int h) 
{
	theWorld.setWH(w, h);
	theWorld.setAspectRatio(float(w)/float(h)); // set new aspect ratio
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update() 
{
	theWorld.update(); // update the World
	glutPostRedisplay(); // redraw everything (since camera may move)
}

//----------------------------------------------------------------------
// Draw the entire scene
//
// We clear the buffers using light blue (so the sky is already drawn)
// and then draw the world.
//----------------------------------------------------------------------
void draw() 
{
	glClearColor(0.0, 0.7, 1.0, 1.0); // background (sky) color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	glLoadIdentity(); // reset modelview transformation

	theWorld.draw(); // draw the world

	glutSwapBuffers(); // make it all visible
} 

//----------------------------------------------------------------------
// User-input callbacks
//
// C++ does not allow callbacks to be made to class methods, so 
// these are just redirections to the corresponding World handler.
//----------------------------------------------------------------------
void processNormalKeys(unsigned char key, int xx, int yy) { theWorld.processNormalKeys(key, xx, yy); }
void releaseNormalKeys(unsigned char key, int xx, int yy) { theWorld.releaseNormalKeys(key, xx, yy); }
void pressSpecialKey(int key, int xx, int yy) { theWorld.pressSpecialKey(key, xx, yy); }
void releaseSpecialKey(int key, int xx, int yy)  { theWorld.releaseSpecialKey(key, xx, yy); }
void mouseMove(int xx, int yy)  { theWorld.mouseMove(xx, yy); }
void mouseButton(int button, int state, int xx, int yy)  { theWorld.mouseButton(button, state, xx, yy); }


int _tmain(int argc, char * argv[])
{
	std::cout << "\n\
-----------------------------------------------------------------------\n\
  Project 2- Tommy the Terp:\n\
  - press 'c' to change camera \n\
  - press 'q' or ESC to quit\n\
  - In top-down view: \n\
  -	'w' walk up\n\
  -	's' walk down\n\
  -	'd' walk right\n\
  -	'a' walk left\n\
  - In third persion: \n\
  -	'w' walk straight\n\
  -	'r' rotate camera right\n\
  -	'a' rotate camera left\n\
  - In first person: \n\
 -	'w' walk straight\n\
  -	'r' rotate camera right\n\
  -	'a' rotate camera left\n\
  - Drag mouse to look up, down, left, and right\n\
-----------------------------------------------------------------------\n";
	int W = 800, H = 600;

	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(W, H);
	glutCreateWindow("OpenGL/GLUT Sampe Program");

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(draw); // (re)display callback
	glutIdleFunc(update); // incremental update 
	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutKeyboardUpFunc(releaseNormalKeys);
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	theWorld.init();
	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}

