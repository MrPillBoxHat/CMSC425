#include <iostream>						// input/outout stream

#include <cstdlib>						// C++ standard definitions
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

#include "World.h"

World * world = nullptr;

void changeSize(int x, int y);
void update();
void drawWorld();
void processNormalKeys(unsigned char key, int xx, int yy);
void mouseButton(int button, int state, int xx, int yy);
void processKeyUp(unsigned char key, int x, int y);

using namespace std;

//world dimensions
const static GLdouble WIDTH = 4000;
const static GLdouble HEIGHT = 1000;

int main(int argc, char **argv) 
{
	cout << "Starting.." << endl;

	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Megaman CMSC425");

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(drawWorld); // (re)display callback
	glutIdleFunc(update); // incremental update 
	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutKeyboardUpFunc(processKeyUp);

	world = new World(WIDTH, HEIGHT); // textures have to be loaded after inits

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}

void changeSize(int x, int y) 
{
	 world->setSize(x, y);
}

void update() 
{
	 world->update();
}
void drawWorld() 
{
	 world->draw();
}

void processNormalKeys(unsigned char key, int xx, int yy) 
{
	world->processKeys(key, xx, yy);
}

void processKeyUp(unsigned char key, int x, int y)
{
	world->processKeyUp(key, x, y);
}