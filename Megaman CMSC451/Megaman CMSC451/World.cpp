/*********************************************************************************
* The World Class 
*	Controls everything in the game.
*   By: Nelson Chen
*       Henry Ramos
*********************************************************************************/
#include <windows.h>				// Used for min/max function
#include "World.h"
#include "X.h"
#include "Zero.h"
#include <iostream>					// Uses I/O
#include <GL/glut.h>                // GLUT
#include <list>
#include "constants.h"

#define SET_BG_COLOR glClearColor(0.0, 0.0, 0.0, 1.0)

void done(unsigned char key, int x, int y);
void noDraw() {};

using namespace std;

// Constructor for the World class
World::World(GLdouble w, GLdouble h) 
{
	width = w;
	height = h;
	bg.setBoundary(width, height);
	x = new X();
	x->loadTextures();
	zero = new Zero();
	zero->loadTextures();
	menu = new Main_Menu();
	menu->loadTextures();
	delta_time = 0;
	start_time = glutGet(GLUT_ELAPSED_TIME);
	current_time = 0;
	lapse_time = 0;
	frames = 0;
	fps = 60;
	main_menu = false;
	cmX = 0;
	// Initialize textures for intro and bullet
	loadTextures();
}

World::~World(void) 
{
	delete x;
	delete zero;
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
		// reset timers
		frames = 0;
		lapse_time = 0;
	}

	// check if we need to update the camera
	int state = x->getState();
	switch(state) {
	case RUN:
	case DASH: // move camera
		{
			// check how fast to move
			const GLdouble diff = (RUN == state) ? CM_WALK : CM_DASH;

			if(x->getDirection() == RIGHT)
				cmX = min(width-bg.viewWidth, cmX + diff);
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
	// Draw whats on the screen depending on state of the game
	if(main_menu){
		enableTextures();
		menu->draw();
	} else {
		bg.draw();

		enableTextures();
		glColor4f(1.0, 1.0, 1.0, 1.0); // Set color
		bullet_draw(); // Draws all bullets on map
		zero->draw(); // Draws zero
		x->draw(); // Draws X
	}
	// disable texturings
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D); 
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
	gluOrtho2D(cmX, cmX + bg.viewWidth, 0, bg.viewHeight);     // one to one
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();                        // request redisplay
}

// Process Keyboard events
void World::processKeys(unsigned char key, int x_coord, int y_coord) 
{
	if(main_menu){
		processKeysMenu(key);
	} else {
		processKeysGame(key);
	}
}

// Process Keys when in menu
void World::processKeysMenu(unsigned char key)
{
	int state = menu->getMenuState();
	if(state == INTRO || state == INTRO_PRESS){
		if(key == 13){
			menu->setMenuState(TRAINING);
		}
	} else {
		switch(key)
		{
			// Move cursor up
			case 'w':
				// if cursor is on continue
				if(state == CONTINUE){
					menu->setMenuState(NEWGAME);
				// if cursor is on option
				} else if(state == OPTION){
					menu->setMenuState(CONTINUE);
				// if cursor is on Training
				} else if(state == TRAINING){
					menu->setMenuState(OPTION);
				// if cursor is new game
				} else {
					menu->setMenuState(TRAINING);
				}
				break;
			
			// Move cursor down
			case 's':
				// if cursor is on continue
				if(state == CONTINUE){
					menu->setMenuState(OPTION);
				// if cursor is on option
				} else if(state == OPTION){
					menu->setMenuState(TRAINING);
				// if cursor is on new game
				} else if(state == NEWGAME){
					menu->setMenuState(CONTINUE);
				// if cursor is on training
				} else {
					menu->setMenuState(NEWGAME);
				}
				break;
			
			// Select cursor
			case 13:
				// if cursor is on continue
				if(state == CONTINUE){
					// load save state

				// if cursor is on Training
				} else if(state == OPTION){
					// Open option screen

				// if cursor is on option
				} else if(state == TRAINING){
					// Start game in training mode
					main_menu = false;

				// if cursor is on new game
				} else {
					// Start game
					break;
				}
		}
	}
}

// Process Keys when in game
void World::processKeysGame(unsigned char key)
{
	const int old = cmX;
	int hero_state = x->getState();
	if(hero_state != ENTRY){
		switch(key)
		{
			// Jump
			case MOVE_JUMP:
				// If not already in the air
				if(hero_state != JUMP){
					x->resetTexture();
					x->setState(JUMP);
				} // else do nothing
				break;

			// Kneel
			case 's':
				break;

			// Move Left
			case MOVE_LEFT:
				// If not in jump animation
				if(hero_state != JUMP && hero_state != DASH){
					x->resetTexture();
					x->setState(RUN);
				}
				// Register button pressed
				x->setButtons(RUN, true);
				// Change direction
				x->setDirection(LEFT);
				break;

			// Move Right
			case MOVE_RIGHT:
				// If not in jump animation
				if(hero_state != JUMP && hero_state != DASH){
					x->resetTexture();
					x->setState(RUN);
				}
				// Register button pressed
				x->setButtons(RUN, true);
				// Change direction
				x->setDirection(RIGHT);
				break;

			// Fire
			case MOVE_FIRE:
				// Can only fire max 3 times
				if(x_bullets.size() < 3){
					X_Bullet *temp = new X_Bullet(x->getCannon(), x->getDirection());
					// Create bullet from cannon position
					x_bullets.push_front(*temp);
					x->setFrameOn();
					x->setState(FIRE);
					// If not in the air, reset texture frame
					if(hero_state != JUMP){
						x->resetTexture();
					}
				}
				break;

			// Dash
			case MOVE_DASH:
				// if X not in the air and not already dashing
				if(hero_state != JUMP && hero_state != DASH){
					x->resetTexture();
					x->setState(DASH);
				}
				break;
		}
	}
	update();
}

// Process up key
void World::processKeyUp(unsigned char key, int x_coord, int y_coord)
{
	// Register key-up only if not in main menu
	if(!main_menu){
		int hero_state = x->getState();
		switch(key)
		{	
			case 's': // Kneel
			case MOVE_LEFT: // Move Left
			case MOVE_RIGHT: // Move Right
				if(hero_state != JUMP && hero_state != ENTRY && hero_state != DASH){
					// Reset state
					x->setState(STAND);
					x->resetTexture();
				}
				x->setButtons(RUN, false);
					break;
			
			// Fire
			case MOVE_FIRE:
				// Fire charged shot
				break;
		}
	}
}

// Loads all textures for bullets
void World::loadTextures()
{
	loadXBullet();
	loadZBullet();
}

// Draw X_bullet
void World::bullet_draw()
{
	// Go through each bullet in the world and draw them
	list<X_Bullet>::iterator it = x_bullets.begin();
	while(it != x_bullets.end()){
		if(it->collision(zero)){
			zero->setState(DAMAGE);
		}
		it->draw(textures);
		// If bullet reaches end of the screen, delete it
		if(it->getX1() <= cmX-20 || it->getX2() >= bg.viewWidth+cmX+20){
			it = x_bullets.erase(it);
		// If bullet hits something
		} else {
			it++;
		}
	}
}

// Load XBullet texture
void World::loadXBullet()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[XBULLET] = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/Bullet/X_Bullet_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[XBULLET] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "WorldtextureID: " << textures[XBULLET] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[XBULLET]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textures[XBULLETDIE] = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/Bullet/splat.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[XBULLETDIE] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "WorldtextureID: " << textures[XBULLETDIE] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[XBULLETDIE]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void World::loadZBullet()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[Z_BULLET_LEFT] = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Bullet/Zero_Bullet_Right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[Z_BULLET_LEFT] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "WorldtextureID: " << textures[Z_BULLET_LEFT] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[Z_BULLET_LEFT]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textures[Z_BULLET_RIGHT] = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Bullet/Zero_Bullet_Right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[Z_BULLET_RIGHT] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "WorldtextureID: " << textures[Z_BULLET_RIGHT] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[Z_BULLET_RIGHT]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// set the common options for textures
void World::enableTextures()
{
	// Enables texturess
	glEnable(GL_TEXTURE_2D); // enable texturing
	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void done(unsigned char key, int x, int y) {
	
}