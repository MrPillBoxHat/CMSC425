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
#include <list>

#define SET_BG_COLOR glClearColor(0.0, 0.0, 0.0, 1.0)

void done(unsigned char key, int x, int y);
void noDraw() {};

//movement of camera TODO sync this up with X
const GLdouble World::CM_WALK = 1.0;
const GLdouble World::CM_DASH = 5.0;

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
	// Initialize bullet texture
	loadTexture();
}

World::~World(void) 
{
	delete x;
}

void World::update(void) 
{
	// Controls Frames per Second of the game
	current_time = glutGet(GLUT_ELAPSED_TIME); // Gets current time
	delta_time += current_time - start_time; // Gets change in time
	start_time = current_time; // Resets start time
	lapse_time += delta_time; // Increment total time

	if(delta_time < ( 1000.0 / fps))
		return;  // don't do anything

	// Updates timer information
	frames++;
	delta_time = 0;
	if(lapse_time > 1000){
		cout << "FPS: " << frames << endl;
		// reset timers
		frames = 0;
		lapse_time = 0;
	}

	// check if we need to update the camera
	int state = x->getState();
	switch(state) {
	case X::MOVE:
	case X::DASH: // move camera
		{
			// check how fast to move
			const GLdouble diff = (X::MOVE == state) ? CM_WALK : CM_DASH;

			if(x->getDirection() == X::RIGHT)
				cmX = min(width-1, cmX + diff);
			else
				cmX = max(0, cmX - diff);

			updateView();
			break;
		}
	default:
		glutPostRedisplay();
		break;
	}
}


void World::draw(void) 
{
	// Draw
	SET_BG_COLOR;
	glClear(GL_COLOR_BUFFER_BIT);
	// background
	draw_helper();
	glutSwapBuffers();
}

void World::draw_helper()
{
	bg.draw();
	// Enables texturess
	glEnable(GL_TEXTURE_2D); // enable texturing
	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0); // Set color
	bullet_draw(); // Draws all bullets on map
	x->draw(); //Draws X
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D); // disable texturing
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
				if(hero_state != x->JUMP && hero_state != x->DASH){
					x->resetTexture();
					x->setState(x->MOVE);
					// camera movement
					cmX = max(0, cmX - CM_WALK);
				}
				// Register button pressed
				x->setButtons(x->MOVE, true);
				// Change direction
				x->setDirection(x->LEFT);
				break;

			// Move Right
			case MOVE_RIGHT:
				// If not in jump animation
				if(hero_state != x->JUMP && hero_state != x->DASH){
					x->resetTexture();
					x->setState(x->MOVE);
					// Camera movement
					cmX = min(width-1, cmX + CM_WALK);
				}
				// Register button pressed
				x->setButtons(x->MOVE, true);
				// Change direction
				x->setDirection(x->RIGHT);
				break;

			// Fire
			case MOVE_FIRE:
				// Can only fire max 3 times
				if(bullets.size() < 3){
					X_Bullet *temp = new X_Bullet(x->getCannon(), x->getDirection());
					// Create bullet from cannon position
					bullets.push_front(*temp);
					x->resetTexture();
					x->setState(x->FIRE);
				}
				break;

			// Dash
			case MOVE_DASH:
				// if X not in the air and not already dashing
				if(hero_state != x->JUMP && hero_state != x->DASH){
					x->resetTexture();
					x->setState(x->DASH);
				}
				break;
		}
	}

	//cout << "cmX = " << cmX << endl;
	/*if(old != cmX)
		updateView();
	else
		glutPostRedisplay();*/
	update();
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
			// Fire charged shot
			break;
	}
}

void World::loadTexture()
{
	/* loads entry image directly as a new OpenGL texture */
	bullet_texture = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/Bullet/X_Bullet_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == bullet_texture )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "textureID2: " << bullet_texture << endl;

	glBindTexture(GL_TEXTURE_2D, bullet_texture); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void World::bullet_draw()
{
	// Go through each bullet in the world and draw them
	list<X_Bullet>::iterator it = bullets.begin();
	while(it != bullets.end()){
		it->draw(bullet_texture);
		// If bullet reaches end of map, delete it
		if(it->getX2() >= 800.0){
			it = bullets.erase(it);
		} else {
			it++;
		}
	}
}

void done(unsigned char key, int x, int y) {
	
}

/*
void World::update(void) 
{
	// check if we need to update the camera
	switch(x->getState()) {
	case x->MOVE:
		if(x->getDirection() == x->RIGHT)
			cmX = min(width-1, cmX + CM_DIFF);
		else
			cmX = max(0, cmX - CM_DIFF);

		updateView();
		break;
	case X::DASH: // move camera at faster pace
		cout << "in update(), dashing!" << endl;
		updateView();
		break;
	default:
		glutPostRedisplay();
		break;
	}
}
*/

/*void World::draw(void) 
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
		draw_helper();
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
}*/