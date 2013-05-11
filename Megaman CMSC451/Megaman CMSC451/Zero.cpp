/******************************************************
* Zero Class
*	Contains all function implementations
*   and actions of the character
*******************************************************/

#include <iostream>						// input/outout stream
#include <cstdlib>						// C++ standard definitions
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL
#include "SOIL.h" 						// Library for loading images
#include "Zero.h" 						// Zero header file
#include "constants.h"
using namespace std;

// Constructor
Zero::Zero()
{
	health = 140;
	// Coordinates of entry
	x1 = 403.5;
	x2 = 532.5;
	y1 = 499.0;
	y2 = 627.0;
	// Cannon position after entry animation
	cannon_position[0] = 477.4;
	cannon_position[1] = 508.0;
	cannon_position[2] = 114.0;
	cannon_position[3] = 151.0;
	// collision box
	hit_box[0] = 451.0;
	hit_box[1] = 484.2;
	hit_box[2] = 100.0;
	hit_box[3] = 145.0;
	state = ENTRY;
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	direction = LEFT;
	counter = 0; // Counter is to keep track of FPS
	// initialize buttons and health blocks to false;
	for(int i = 0; i < 9; i++){
		buttons[i] = false;
		health_blocks[i] = false;
	}
	for(int i = 9; i < 28; i++){
		health_blocks[i] = false;
	}
	init_health = false;
}

// Getter for Zero's position
float *Zero::getHitBox()
{
	return hit_box;
}

void Zero::setPosition(float xx1, float xx2, float yy1, float yy2)
{
	x1 += xx1;
	x2 += xx2;
	y1 += yy1;
	y2 += yy2;
}

// Draw Zero
void Zero::draw()
{
	// Move Zero in the world
	move();
	// Draw Zero's health bar
	if(state != ENTRY){
		drawHealth();
	}
	// Determines which action to draw
	switch(state)
	{
		case ENTRY:
			entry();
			break;
		case STAND:
			stand();
			break;
		case RUN:
			run();
			break;
		case JUMP:
			jump();
			break;
		case FIRE:
			fire();
			break;
		case SABER:
			saber();
			break;
		case DASH:
			dash();
			break;
		case DAMAGE:
			damage();
			break;
		case DIE:
			die();
			break;
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}
		
// Move Zero's coordinates
void Zero::move()
{
	// Dash movement (faster movement)
	if(buttons[DASH]){
		if(direction == LEFT){
			x1 -= CM_DASH;
			x2 -= CM_DASH;
			cannon_position[0] -= CM_DASH;
			cannon_position[1] -= CM_DASH;
			hit_box[0] -= CM_DASH;
			hit_box[1] -= CM_DASH;
		} else {
			x1 += 5.0;
			x2 += 5.0;
			cannon_position[0] += CM_DASH;
			cannon_position[1] += CM_DASH;
			hit_box[0] += CM_DASH;
			hit_box[1] += CM_DASH;
		}
	// Normal movements
	} else {
		// Move Zero horizontally
		if(buttons[RUN]){
			if(direction == LEFT){
				x1 -= CM_WALK;
				x2 -= CM_WALK;
				cannon_position[0] -= CM_WALK;
				cannon_position[1] -= CM_WALK;
				hit_box[0] -= CM_WALK;
				hit_box[1] -= CM_WALK;
			} else {
				x1 += 2.0;
				x2 += 2.0;
				cannon_position[0] += CM_WALK;
				cannon_position[1] += CM_WALK;
				hit_box[0] += CM_WALK;
				hit_box[1] += CM_WALK;
			}
		}
	}
	// Move Zero vertically
	if(buttons[JUMP]){
		// FPS control
		if(counter %5 == 0){
			if(x1_tcoord >= 0.72){
			// no change in position
			} else if(x1_tcoord >= 0.36 && x1_tcoord < 0.72){
			// Zero is falling back down
				y1 -= 22.0;
				y2 -= 22.0;
				cannon_position[2] -= 22.0;
				cannon_position[3] -= 22.0;
				hit_box[2] -= 22.0;
				hit_box[3] -= 22.0;
			} else {
				// Move Zero up
				y1 += 22.0;
				y2 += 22.0;
				cannon_position[2] += 22.0;
				cannon_position[3] += 22.0;
				hit_box[2] += 22.0;
				hit_box[3] += 22.0;
			}
		}
	}
}

// Draws Zero's Health bar
void Zero::drawHealth()
{
	// Draw the bar
	glBindTexture(GL_TEXTURE_2D, textures[HEALTH_BAR]); // select the active texture
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(0.0, 0.0); glVertex2d(718, 194);
		glTexCoord2d(1.0, 0.0); glVertex2d(772, 194);
		glTexCoord2d(1.0, 1.0); glVertex2d(772, 383);
		glTexCoord2d(0.0, 1.0); glVertex2d(718, 383);
	glEnd();
	// If health was already drawn
	if(!init_health && counter % 3 == 0){
		gainHealth((health/5)-1); // max life (blocks)
	}
	// Draw the blocks
	glBindTexture(GL_TEXTURE_2D, textures[HEALTH_BLOCK]); // select the active texture
	// position of health blocks
	float xx1 = 727.0;
	float xx2 = 759.0;
	float yy1 = 245.0;
	float yy2 = 253.0;
	int i = 0; // counter to iterate through health_blocks
	// iterate through the blocks and draw them
	while(i <= 27 && health_blocks[i]){
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(0.0, 0.0); glVertex2d(xx1, yy1);
			glTexCoord2d(1.0, 0.0); glVertex2d(xx2, yy1);
			glTexCoord2d(1.0, 1.0); glVertex2d(xx2, yy2);
			glTexCoord2d(0.0, 1.0); glVertex2d(xx1, yy2);
		glEnd();
		yy1 += 4.0;
		yy2 += 4.0;
		i++; // increment count
	}
}

// Draws the animation that fills Zero's health
void Zero::gainHealth(int block_number)
{
	// if last block is drawn, done
	if(health_blocks[block_number]){
		init_health = true;
	// Draw 1 block
	} else {
		// iterate through health bar
		for(int i = 0; i < 28; i++){
			// if the bar is not there
			if(!health_blocks[i]){
				// draw the bar
				health_blocks[i] = true;
				break;
			}
		}
	}
}

// Decreases the amount of health blocks
void Zero::depleteHealth(int block_number)
{
	// start at the end of the array
	int i = 27;
	// sets all health blocks to false
	while(i >= block_number){
		if(health_blocks[i]){
			health_blocks[i] = false;
		}
		i--;
	}
}

// Actions
// Zero Entry Animation
void Zero::entry()
{
	// How many frames to jump
	float x_offset = 0.125;
	float y_offset = 0.5;
	// Draws the frame
	glBindTexture(GL_TEXTURE_2D, textures[ENTRY_TEXUTRE]); // select the active texture
	glBegin(GL_POLYGON); // draw the object(s)
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset); glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Update frame pointers
	// If Zero has not landed
	if(y1 != 64.0){
		y1 -= 5.0;
		y2 -= 5.0;
	} else {
		if(counter % 5 == 0){
			// go to next frame
			x1_tcoord += x_offset;
			if(x1_tcoord >= 1.0){
				// Move down 1 row
				y2_tcoord -= y_offset;
				// When Finished, load stand
				if(y2_tcoord <= 0.0){
					// Go into standing state
					state = STAND;
					// Resets coordinates
					x1 = 440.0;
					x2 = 491.2;
					y1 = 97.0;
					y2 = 161.0;
					resetTexture();
				} else {
					// Reset x frame pointer
					x1_tcoord = 0.0;	
				}
			}
		}
	}
}

// Zero standing Animation
void Zero::stand()
{
	// How many frames to jump
	float x_offset = 0.099609375;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[STAND_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[STAND_LEFT]); // select the active texture
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Want to draw 5 frames per second
	if(counter % 15 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 0.99609375){
			x1_tcoord = 0.0;
		}
	}
}

// Zero running Animation
void Zero::run(){
	// How many frames to jump
	float x_offset = 0.125;
	float y_offset = 0.5;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[RUN_RIGHT]); // select the active texture
		// Readjust cannon position
		cannon_position[0] = x2 - 21.8;
		cannon_position[1] = x2 + 8.8;
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[RUN_LEFT]); // select the active texture
		// Readjust cannon position
		cannon_position[0] = x1 - 8.8;
		cannon_position[1] = x1 + 21.8;
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Update frame pointers
	if(counter % 5 == 0){
		// go to next frame
		x1_tcoord += x_offset;
		if(x1_tcoord >= 1.0){
			// Reset x frame pointer
			x1_tcoord = 0.0;
			// Move down 1 row
			y2_tcoord -= y_offset;
			// When animation reaches end
			// Start on 3rd frame of beginning
			if(y2_tcoord <= 0.0){
				y2_tcoord = 1.0;
				x1_tcoord = 0.25;
			}
		}
	}
}

// Zero jumping animation
void Zero::jump()
{
	// How many frames to jump
	float x_offset = 0.0666666666666666666666666;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[JUMP_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[JUMP_LEFT]); // select the active texture
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Update frame pointers
	if(counter % 5 == 0){
		// if max height frame is reached
		// go to next frame
		x1_tcoord += x_offset;
		// When finished playing
		if(x1_tcoord >= 1.0){
			// Reset state
			x1_tcoord = 0.0;
			if(buttons[RUN]){
				state = RUN;
				x1_tcoord = 0.0;
				y2_tcoord = 0.5;
			} else {
				state = STAND;
			}
			buttons[JUMP] = false;
			buttons[DASH] = false;
			y2 -= 64.0;
		}
	}
}

// Zero Fire Animation
void Zero::fire()
{
	// How many frames to jump
	float x_offset = 0.166015625;
	float y_offset = 0.5;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[FIRE_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[FIRE_LEFT]); // select the active texture
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1-20.0, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1-20.0, y2);
	glEnd();
	// Want to draw 5 frames per second
	if(counter % 6 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 0.99609375){
			x1_tcoord = 0.0;
			y2_tcoord -= y_offset;
			if(y2_tcoord <= 0){
				// Reset texture coordinates
				if(direction == LEFT){
					setPosition(-8.0, -8.0, 0.0, 0.0);
				} else {
					setPosition(-12.0, -12.0, 0.0, 0.0);
				}
				resetTexture();
				state = STAND;
			}
		}
	}
}

// Zero saber attack Animation
void Zero::saber()
{
	// How many frames to jump
	float x_offset = 0.0712890625;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[SABER_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[SABER_LEFT]); // select the active texture
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Want to draw 5 frames per second
	if(counter % 3 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 0.998046875){
			// Reset texture position
			if(direction == LEFT){
				setPosition(60.0, -30.0, 7.0, -48.0);
			} else {
				setPosition(30.0, -60.0, 7.0, -48.0);
			}
			resetTexture();
			state = STAND;
		}
	}
}

// Zero Dash animation
void Zero::dash()
{
	// How many frames to jump
	float x_offset = 0.2;
	float y_offset = 0.5;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[DASH_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[DASH_LEFT]); // select the active texture
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Want to draw 5 frames per second
	if(counter % 3 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 1.0){
			x1_tcoord = 0.0;
			y2_tcoord -= y_offset;
			if(y2_tcoord <= 0){
				// If player is holding move change to run
				if(buttons[RUN]){
					x1_tcoord = 0.375;
					state = RUN;
				// If player is not holding move, change to stand
				} else {
					y2_tcoord = 1.0;
					state = STAND;
				}
				// Adjust Zero's texture coordinates
				setPosition(22.5, -22.5, 0.0, 0.0);
				buttons[DASH] = false;
				y2_tcoord = 1.0;
			}
		}
	}
}

// Responses
// Zero damage animation
void Zero::damage()
{
	// How many frames to jump
	float x_offset = 0.166015625;
	float y_offset = 0.5;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[DAMAGE_RIGHT]); // select the active texture
		x1 += 0.1;
		x2 += 0.1;
		hit_box[0] += 0.1;
		hit_box[1] += 0.1;
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[DAMAGE_LEFT]); // select the active texture
		x1 -= 0.1;
		x2 -= 0.1;
		hit_box[0] -= 0.1;
		hit_box[1] -= 0.1;
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Want to draw 5 frames per second
	if(counter % 3 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 0.99609375){
			x1_tcoord = 0.0;
			y2_tcoord -= y_offset;
			if(y2_tcoord <= 0){
				resetTexture();
				state = STAND;
			}
		}
	}
}

// Zero death animation
void Zero::die()
{

}

// Loads all textures
void Zero::loadTextures()
{
	loadEntry();
	loadStand();
	loadMove();
	loadJump();
	loadFire();
	loadSaber();
	loadDash();
	loadHealth();
	loadDamage();
	loadDie();
}

// Load Zero's Entry texture
void Zero::loadEntry()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Entry/Zero_Entry_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[ENTRY_TEXUTRE] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's standing texture
void Zero::loadStand()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/stand/stand_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[STAND_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/stand/stand_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[STAND_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Running texture
void Zero::loadMove()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Run/run_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[RUN_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Run/run_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[RUN_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Jump texture
void Zero::loadJump()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/jump/jump_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[JUMP_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/jump/jump_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[JUMP_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Saber slash texture
void Zero::loadSaber()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Saber/saber_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[SABER_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Saber/saber_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[SABER_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Fire texture
void Zero::loadFire()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Fire/Fire_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[FIRE_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Fire/Fire_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[FIRE_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Dash texture
void Zero::loadDash()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/dash/dash_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[DASH_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/dash/dash_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[DASH_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Health Bar texture
void Zero::loadHealth()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Health_bar/health_bar.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[HEALTH_BAR] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/health_block.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[HEALTH_BLOCK] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Damage texture
void Zero::loadDamage()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/damage/back/damage_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[DAMAGE_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/damage/back/damage_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "ZeroTextureID: " << textureID << endl;

	textures[DAMAGE_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load Zero's Death texture
void Zero::loadDie()
{

}