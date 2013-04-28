#include <cstdlib>						// C++ standard definitions
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

#include "World.h"

World world;

void changeSize(int x, int y);
void update();
void drawWorld();
void processNormalKeys(unsigned char key, int xx, int yy);
void mouseButton(int button, int state, int xx, int yy);


int main(int argc, char **argv) 
{
	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	glutCreateWindow("Megaman CMSC425");

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(drawWorld); // (re)display callback
	glutIdleFunc(update); // incremental update 
	//glutIgnoreKeyRepeat(); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	//glutMotionFunc(); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	//glutSpecialFunc(); // process special key pressed
	//glutSpecialUpFunc(); // process special key release

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}

void changeSize(int x, int y) 
{
	 world.setSize(x, y);
}

void update() 
{
	 world.update();
}
void drawWorld() 
{
	 world.draw();
}

void mouseButton(int button, int state, int x, int y) 
{
	 world.mouseButton(button, state, x, y);
}

void processNormalKeys(unsigned char key, int xx, int yy) 
{
	world.processKeys(key, xx, yy);
}
