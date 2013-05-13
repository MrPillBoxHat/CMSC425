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
#include "Saber.h"

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
	zero = NULL;
	initZero = false;
	menu = new Main_Menu();
	menu->loadTextures();
	zAI = NULL;
	missile = NULL;
	saber = NULL;
	create = false;
	// initialize world instance variables
	width = w;
	height = h;
	bg.setBoundary(width, height);
	bg.initGround();
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
	// AI for Zero and collision can only be used if Zero is initialized
	if(zero != NULL){
		// Ask AI what it wants to do
		if(zero->getInit()){
			processAI();
		}
		// Detect X colliding with Zero
		if(!x->ifInvinciple()){
			x->detec_collision(zero);
		}
	}
	
	float *x_position = x->getHitBox();
	// If X reaches boss room
	if(!initZero && x_position[0] >= 3555.0){
		initBossRoom();
	}
	updateView();
}

void World::initBossRoom()
{
	initZero = true;
	zero = new Zero();
	zero->loadTextures();
	zAI = new ZeroAI(zero, x);
	resetHitBox();
	x->setState(STAND);
	x->resetTexture();
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

		// Hit box for testing
		float *test = x->getHitBox();
		glColor4f(255, 255, 0, 1);
		glRectf(test[0], test[2], test[1], test[3]);
		/*
		float *test2 = zero->getHitBox();
		glColor4f(255, 255, 0, 1);
		glRectf(test2[0], test2[2], test2[1], test2[3]);*/

		enableTextures();
		glColor4f(1.0, 1.0, 1.0, 1.0); // Set color
		if(zero != NULL){
			zero->draw(); // Draws zero
			createMissiles(); // Draw zero objects
		}
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
	// position at X
	const int pt = x->middle();	
	GLdouble diff = bg.viewWidth;
	cout << "mid-point = " << pt << " , viewWidth = " << bg.viewWidth << endl;
	if(pt >= 0 && pt >= (bg.viewWidth / 2) ) 
	{
		cmX = pt - (bg.viewWidth / 2);
	}
	gluOrtho2D(cmX, cmX + diff, 0, bg.viewHeight);     // one to one
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
	if(hero_state != ENTRY && hero_state != DAMAGE && (zero == NULL || zero->getInit())){
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
			// Move Right
			case MOVE_RIGHT:
				// If not in jump animation
				if(hero_state != JUMP && hero_state != DASH && hero_state != DAMAGE){
					x->resetTexture();
					x->setState(RUN);
				}
				// Change direction if in a dash
				if(key == MOVE_LEFT){
					// Get out of dash state if moving in opposite direction
					if(x->getDirection() == RIGHT && hero_state == DASH){
						x->setButtons(DASH, false);
						x->setHitBox(0.0, -8.0, 0.0, 12.0);
						x->resetTexture();
						x->setState(RUN);
					}
					x->setDirection(LEFT);
				} else if (key == MOVE_RIGHT){
					// Get out of dash state if moving in opposite direction
					if(x->getDirection() == LEFT && hero_state == DASH){
						x->setButtons(DASH, false);
						x->setHitBox(8.0, 0.0, 0.0, 12.0);
						x->resetTexture();
						x->setState(RUN);
					}
					x->setDirection(RIGHT);
				}
				// Register button pressed
				x->setButtons(RUN, true);
				break;

			// Fire
			case MOVE_FIRE:
				// Can only fire max 3 times
				if(x_bullets.size() < 3){
					X_Bullet *temp = new X_Bullet(x->getCannon(), x->getDirection());
					// Create bullet from cannon position
					x_bullets.push_front(*temp);
					if(hero_state == DASH){
						// Get out of dash animation
						if(x->getDirection() == RIGHT){
							x->setButtons(DASH, false);
							x->setHitBox(0.0, -8.0, 0.0, 12.0);
						} else {
							x->setButtons(DASH, false);
							x->setHitBox(8.0, 0.0, 0.0, 12.0);
						}
					}
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
					if(x->getDirection() == RIGHT){
						x->setHitBox(0.0, 8.0, 0.0, -12.0);
					} else {
						x->setHitBox(-8.0, 0.0, 0.0, -12.0);
					}
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
	update();
}

// Process AI commands
void World::processAI()
{
	int action = zAI->getAction();
	switch(action)
	{
		// Stand and do nothing
		case STAND:
			zero->resetTexture();
			zero->setState(STAND);
			break;
		
		// Fire
		case FIRE:
			if(zero->getDirection() == LEFT){
				zero->setPosition(8.0, 8.0, 0.0, 0.0);
			} else {
				zero->setPosition(12.0, 12.0, 0.0, 0.0);
			}
			// Create bullet from cannon position
			zero->resetTexture();
			zero->setState(FIRE);
			break;

		case SABER_MISSILE:
		case SABER:
			// Adjust based on zero's direction
			if(zero->getDirection() == LEFT){
				zero->setPosition(-60.0, 30.0, -7.0, 48.0);
			} else {
				zero->setPosition(-30.0, 60.0, -7.0, 48.0);
			}
			zero->resetTexture();
			if(action == SABER){
				zero->setState(SABER);
			} else {
				zero->setState(SABER_MISSILE);
			}
			break;

		case DASH:
			// Adjust Zero's texture coordinates
			zero->setPosition(-22.5, 22.5, 0.0, 0.0);
			zero->resetTexture();
			zero->setState(DASH);
			break;

		case RUN:
			// Adjust Zero's texture coordinates
			zero->resetTexture();
			zero->setState(RUN);
			break;
	}
}

// Create all bullets and missile objects
void World::createMissiles()
{
	int z_state = zero->getState();
	if(z_state == FIRE){
		// If on the correct frame, create bullet
		float *tempInt = zero->getTextureCoord();
		if(tempInt[0] >= 0.66 && tempInt[0] < 0.76 && tempInt[1] == 0.5 && create == false){
			Z_Bullet *temp = new Z_Bullet(zero->getCannon(), zero->getDirection());
			z_bullets.push_front(*temp);
			create = true;
		}
		// If on the correct frame, create saber object
	} else if (z_state == SABER || z_state == SABER_MISSILE){
		float *tempInt = zero->getTextureCoord();
		// Create saber object
		if(tempInt[0] >= 0.42 && tempInt[0] < 0.45){
			saber = new Saber(zero->getCannon(), zero->getDirection(), 1);
		} else if (tempInt[0] >= 0.45){
			delete(saber);
			saber = NULL;
		}

		// Create a missile object
		if(z_state == SABER_MISSILE){
			if(tempInt[0] >= 0.25 && tempInt[0] < 0.35 && create == false){
				missile = new Saber(zero->getCannon(), zero->getDirection());
				create = true;
			}
		}

	// Nothing was created
	} else {
		create = false;
	}
}

// Draw all bullets/missiles on the map
void World::bullet_draw()
{
	// Go through each X_bullet in the world and draw them
	list<X_Bullet>::iterator it = x_bullets.begin();
	while(it != x_bullets.end()){
		// Make sure zero is created
		if(zero != NULL){
			// Take damage only if not already in damage state
			if(it->collision(zero) && !zero->ifInvincible()){
				if(zero->getState() == STAND){
					zero->resetTexture();
					zero->setState(DAMAGE);
				}
				zero->setHealth(it->getDamage());
				zero->depleteHealth(zero->getHealth()/5);
				zero->setInvincibility();
				it->setX1Coord(0.0);
			}
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
		// Take damage only if not already in damage animation
		if(it2->collision(x) && !x->ifInvinciple()){
			resetHitBox();
			damage(it2->getDamage(), x->getHealth()/5);
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
		// Take damage only if not already in damage animation
		if(missile->collision(x) && !x->ifInvinciple()){
			resetHitBox();
			damage(missile->getDamage(), x->getHealth()/5);
		}
		missile->draw(textures);
		// If missile reaches end of the screen, delete it
		if(missile->getX1() <= cmX-20 || missile->getX2() >= bg.viewWidth+cmX+20){
			delete(missile);
			missile = NULL;
		}
	}

	// Detect whether saber hit X
	if(saber != NULL){
		if(saber->collision(x) && !x->ifInvinciple()){
			resetHitBox();
			damage(saber->getDamage(), x->getHealth()/5);
		}
	}
}

// helper function that does damage mechanics
void World::damage(int damage, int health)
{
	x->resetTexture();
	x->setState(DAMAGE);
	x->setHealth(damage);
	x->depleteHealth(health);
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

void World::resetHitBox()
{
	bool ifXAction = x->getState() == DASH || x->getState() == RUN;
	// Get out of dash animation and stop moving
	if(ifXAction){
		x->setButtons(DASH, false);
		x->setButtons(RUN, false);
		if(x->getDirection() == RIGHT){
			x->setHitBox(0.0, -8.0, 0.0, 12.0);
		} else {
			x->setHitBox(8.0, 0.0, 0.0, 12.0);
		}
	}
}

void done(unsigned char key, int x, int y) {
	
}