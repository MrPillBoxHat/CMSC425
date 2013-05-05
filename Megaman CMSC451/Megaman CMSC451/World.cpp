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

#define SET_BG_COLOR glClearColor(0.0, 0.0, 0.0, 1.0)

void done(unsigned char key, int x, int y);
void noDraw() {};

using namespace std;

// Constructor for the World class
World::World(GLdouble w, GLdouble h) 
{
	width = w;
	height = h;
	x = new X();
	x->loadTextures();
	delta_time = 0;
	start_time = glutGet(GLUT_ELAPSED_TIME);
	current_time = 0;
	lapse_time = 0;
	frames = 0;
	fps = 60;
	cmX = 0;
}


World::~World(void) 
{
	delete x;
}


void World::update(void) 
{
	// check if we need to update the camera
	if(x->getState() == x->MOVE) {
		if(x->getDirection() == x->RIGHT)
			cmX = min(width-1, cmX + CM_DIFF);
		else
			cmX = max(0, cmX - CM_DIFF);

		updateView();
	} else
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
		// background
		bg.draw();
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
	glViewport(0, 0, w, h);
	updateView();
}

void World::updateView()
{
	glMatrixMode(GL_PROJECTION);                // update projection
    glLoadIdentity();
	gluOrtho2D(cmX, cmX + 800, 0, 400);          // one to one
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();                        // request redisplay
}
// Process Keyboard events
void World::processKeys(unsigned char key, int x_coord, int y_coord) 
{
	const int old = cmX;
	int hero_state = x->getState();
	if(hero_state != x->ENTRY){
		switch(key)
		{
			// Jump
			case MOVE_JUMP:
				// If not already in the air
				if(hero_state != x->JUMP){
					x->resetTexture();
					x->setState(x->JUMP);
				} // else do nothing
				break;

			// Kneel
			case 's':
				break;

			// Move Left
			case MOVE_LEFT:
				// If not in jump animation
				if(hero_state != x->JUMP){
					x->resetTexture();
					x->setState(x->MOVE);
				}
				// Register button pressed
				x->setButtons(x->MOVE, true);
				// Change direction
				x->setDirection(x->LEFT);
				// camera movement
				cmX = max(0, cmX - CM_DIFF);
				break;

			// Move Right
			case MOVE_RIGHT:
				// If not in jump animation
				if(hero_state != x->JUMP){
					x->resetTexture();
					x->setState(x->MOVE);
				}
				// Register button pressed
				x->setButtons(x->MOVE, true);
				// Change direction
				x->setDirection(x->RIGHT);
				// Camera movement
				cmX = min(width-1, cmX + CM_DIFF);
				break;

			// Fire
			case MOVE_FIRE:
				if(hero_state != x->JUMP){
					x->resetTexture();
					x->setState(x->FIRE);
				}
				break;

			// Dash
			case MOVE_DASH:
				if(hero_state != x->JUMP){
					x->resetTexture();
					x->setState(x->DASH);
				}
				break;
		}
	}

	//cout << "cmX = " << cmX << endl;
	if(old != cmX)
		updateView();
	else
		glutPostRedisplay();
}

void World::processKeyUp(unsigned char key, int x_coord, int y_coord)
{
	switch(key)
	{		
		case 's': // Kneel
		case MOVE_LEFT: // Move Left
		case MOVE_RIGHT: // Move Right
			if(x->getState() != x->JUMP && x->getState() != x->ENTRY){
				// Reset state
				x->setState(x->STAND);
				x->resetTexture();
			}
			x->setButtons(x->MOVE, false);
			break;
		// Fire
		case MOVE_FIRE:
			x->setState(x->STAND);
			x->resetTexture();
			x->setButtons(x->FIRE, false);
			// Fire charged shot
			break;
		case MOVE_DASH:
			x->setState(x->STAND);
			x->setButtons(x->DASH, false);
			x->resetTexture();
			// Fire charged shot
			break;
	}
}


void done(unsigned char key, int x, int y) {
	
}