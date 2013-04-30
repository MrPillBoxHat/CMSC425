/*********************************************************************************
* The World Class 
*	Controls everything in the game.
*   By: Nelson Chen
*       Henry Ramos
*********************************************************************************/

#include "World.h"
#include "X.h"
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

#define SET_BG_COLOR glClearColor(0.1, 0.5, 0.5, 1.0)

void done(unsigned char key, int x, int y);
void noDraw() {};

using namespace std;

// Constructor for the World class
World::World(unsigned int w, unsigned int h) 
{
	width = width;
	height = height;
	x = new X();
	x->loadTextures();
}


World::~World(void) 
{
	
}


void World::update(void) 
{
	glutPostRedisplay();
}


void World::draw(void) 
{
	SET_BG_COLOR;
	glClear(GL_COLOR_BUFFER_BIT);
	x->draw(); //Draws X
	/* stuff */
	glutSwapBuffers();
}

void World::setSize(int w, int h) 
{
	width = w; height = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);                // update projection
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);          // one to one
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();                        // request redisplay
}
void World::processKeys(unsigned char key, int x, int y) 
{

	glutPostRedisplay();
}

void World::mouseButton(int button, int state, int x, int y) 
{

}


void done(unsigned char key, int x, int y) {
	exit(0);
}