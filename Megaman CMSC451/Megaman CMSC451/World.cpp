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
#include "ZeroAI.h"
#include "saber_missile.h"

#define SET_BG_COLOR glClearColor(0.0, 0.0, 0.0, 1.0)

void done(unsigned char key, int x, int y);
void noDraw() {};

using namespace std;

// Constructor for the World class
World::World(GLdouble w, GLdouble h) 
{
	// Create objects and load their texture
	x = new X();
	x->loadTextures();
	zero = new Zero();
	zero->loadTextures();
	menu = new Main_Menu();
	menu->loadTextures();
	zAI = new ZeroAI(zero, x);
	missile = NULL;
	// initialize world instance variables
	width = w;
	height = h;
	bg.setBoundary(width, height);
	// initialize FPS controller variables
	delta_time = 0;
	start_time = glutGet(GLUT_ELAPSED_TIME);
	current_time = 0;
	lapse_time = 0;
	frames = 0;
	fps = 60;
	// If in main menu
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
	// Ask AI what it wants to do
	if(zero->getInit()){
		processAI();
	}
	// If zero is on the map
	if(zero != NULL && x->getState() != DAMAGE){
		x->detec_collision(zero);
	}
	// Check if zero crashed into X
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

		float *test = x->getHitBox();
		glColor4f(255, 255, 0, 1);
		glRectf(test[0], test[2], test[1], test[3]);
		float *test2 = zero->getHitBox();
		glColor4f(255, 255, 0, 1);
		glRectf(test2[0], test2[2], test2[1], test2[3]);

		enableTextures();
		glColor4f(1.0, 1.0, 1.0, 1.0); // Set color
		zero->draw(); // Draws zero
		x->draw(); // Draws X
		bullet_draw(); // Draws all bullets on map
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
	if(hero_state != ENTRY && (zero == NULL || zero->getInit())){
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
					// Hit box for X
					x->setHitBox(0.0, 8.0, 0.0, -7.0);
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
				if(hero_state != JUMP && hero_state != ENTRY && hero_state != DASH && (zero == NULL || zero->getInit())){
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

// Process AI commands
void World::processAI()
{
	int action = zAI->getAction();
	Z_Bullet *temp;
	switch(action)
	{
		// Stand and do nothing
		case STAND:
			zero->resetTexture();
			zero->setState(STAND);
			break;
		
		// Fire
		case FIRE:
			temp = new Z_Bullet(zero->getCannon(), zero->getDirection());
			if(zero->getDirection() == LEFT){
				zero->setPosition(8.0, 8.0, 0.0, 0.0);
			} else {
				zero->setPosition(12.0, 12.0, 0.0, 0.0);
			}
			// Create bullet from cannon position
			zero->resetTexture();
			z_bullets.push_front(*temp);
			zero->setState(FIRE);
			break;

		case SABER:
			// Adjust based on zero's direction
			if(zero->getDirection() == LEFT){
				zero->setPosition(-60.0, 30.0, -7.0, 48.0);
			} else {
				zero->setPosition(-30.0, 60.0, -7.0, 48.0);
			}
			zero->resetTexture();
			zero->setState(SABER);
			break;

		case DASH:
			// Adjust Zero's texture coordinates
			zero->setPosition(-22.5, 22.5, 0.0, 0.0);
			zero->resetTexture();
			zero->setState(DASH);
			break;

		case RUN:
			// Adjust Zero's texture coordinates
			//zero->setPosition(-22.5, 22.5, 0.0, 0.0);
			zero->resetTexture();
			zero->setState(RUN);
			break;
	}
}

// Draw all bullets/missiles on the map
void World::bullet_draw()
{
	// Go through each X_bullet in the world and draw them
	list<X_Bullet>::iterator it = x_bullets.begin();
	while(it != x_bullets.end()){
		if(it->collision(zero) && zero->getState() != DAMAGE){
			// Reset texture only if not already in damage animation
			zero->resetTexture();
			zero->setState(DAMAGE);
			zero->setHealth(it->getDamage());
			zero->depleteHealth(zero->getHealth()/5);
		}
		// draw bullet
		it->draw(textures);
		// If bullet reaches end of the screen, delete it
		if(it->getX1() <= cmX-20 || it->getX2() >= bg.viewWidth+cmX+20){
			it = x_bullets.erase(it);
		// If bullet hits something
		} else {
			it++;
		}
	}

	// Go through each Z_bullet in the world and draw them
	list<Z_Bullet>::iterator it2 = z_bullets.begin();
	while(it2 != z_bullets.end()){
		if(it2->collision(x) && x->getState() != DAMAGE){
			// Reset texture only if not already in damage animation
			x->resetTexture();
			x->setState(DAMAGE);
			x->setHealth(it2->getDamage());
			x->depleteHealth(x->getHealth()/5);
		}
		// draw bullet
		it2->draw(textures);
		// If bullet reaches end of the screen, delete it
		if(it2->getX1() <= cmX-20 || it2->getX2() >= bg.viewWidth+cmX+20){
			it2 = z_bullets.erase(it2);
		// If bullet hits something
		} else {
			it2++;
		}
	}

	// Draw the saber missile if it exists
	if(missile != NULL){
		if(missile->collision(x) && x->getState() != DAMAGE){
			// Reset texture only if not already in damage animation
			x->resetTexture();
			x->setState(DAMAGE);
			x->setHealth(missile->getDamage());
			x->depleteHealth(x->getHealth()/5);
		}
		missile->draw(textures);
		// If missile reaches end of the screen, delete it
		if(missile->getX1() <= cmX-20 || missile->getX2() >= bg.viewWidth+cmX+20){
			delete(missile);
			missile = NULL;
		}
	}
}

// Loads all textures for bullets
void World::loadTextures()
{
	loadXBullet();
	loadZBullet();
	loadZBulletMissile();
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

	cout << "XBullettextureID: " << textures[XBULLET] << endl;

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

	cout << "XBullettextureID: " << textures[XBULLETDIE] << endl;

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
		"Sprites/Zero/Bullet/Zero_Bullet_left.png",
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

	cout << "ZBullettextureID: " << textures[Z_BULLET_LEFT] << endl;

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
		"Sprites/Zero/Bullet/Zero_Bullet_right.png",
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

	cout << "ZBullettextureID: " << textures[Z_BULLET_RIGHT] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[Z_BULLET_RIGHT]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void World::loadZBulletMissile()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[Z_SABER_LEFT] = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Saber/saber_range_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[Z_SABER_LEFT] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZBullettextureID: " << textures[Z_SABER_LEFT] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[Z_SABER_LEFT]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textures[Z_SABER_RIGHT] = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Saber/saber_range_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[Z_SABER_RIGHT] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZBullettextureID: " << textures[Z_SABER_RIGHT] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[Z_SABER_RIGHT]); // select the active texture
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
	glEnable(GL_TEXTURE_2D);
	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void done(unsigned char key, int x, int y) {
	
}