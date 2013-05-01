/*********************************************************************************
* The World Class 
*	Controls everything in the game.
*   By: Nelson Chen
*       Henry Ramos
*********************************************************************************/

#include <windows.h>				// Used for sleep function
#include "World.h"
#include "X.h"
#include <iostream>					// Uses I/O
#include <GL/glut.h>                // GLUT

#define SET_BG_COLOR glClearColor(0.5, 0.1, 0.5, 1.0)

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
	delta_time = 0;
	start_time = glutGet(GLUT_ELAPSED_TIME);
	current_time = 0;
	lapse_time = 0;
	frames = 0;
	fps = 60;
}


World::~World(void) 
{
	delete x;
}


void World::update(void) 
{
	glutPostRedisplay();
}


void World::draw(void) 
{
	// Controls Frames per Second of the game
	current_time = glutGet(GLUT_ELAPSED_TIME); // Gets current time
	delta_time += current_time - start_time; // Gets change in time
	start_time = current_time; // Resets start time
	lapse_time += delta_time; // Increment total time
	// Determines whether to draw or sleep
	if(delta_time < ( 1000 / fps)) {
		Sleep((1000 / fps) - delta_time);
	} else {
		// Draw
		SET_BG_COLOR;
		glClear(GL_COLOR_BUFFER_BIT);
		x->draw(); //Draws X
		glutSwapBuffers();
		// Updates timer information
		frames++;
		delta_time = 0;
		if(lapse_time > 1000){
			cout << "FPS: " << frames << endl;
			// reset timers
			frames = 0;
			lapse_time = 0;
		}
	}
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
	
}