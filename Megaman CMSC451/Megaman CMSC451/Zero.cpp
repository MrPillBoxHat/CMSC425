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

using namespace std;

// Constructor
Zero::Zero()
{
	health = 50;
	// Coordinates of entry
	x1 = 405.0;
	x2 = 533.0;
	y1 = 500.0;
	y2 = 628.0;
	// Cannon position after entry animation
	position[0] = 477.4;
	position[1] = 508.0;
	position[2] = 114.0;
	position[3] = 151.0;
	state = ENTRY;
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	direction = RIGHT;
	counter = 0; // Counter is to keep track of FPS
	for(int i = 0; i < 9; i++){
		buttons[i] = false;
	}
}

// Draw Zero
void Zero::draw()
{
	// Move Zero in the world
	move();
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
}
		
// Move Zero's coordinates
void Zero::move()
{
	// Dash movement (faster movement)
	if(buttons[DASH]){
		if(direction == LEFT){
			x1 -= 5.0;
			x2 -= 5.0;
			position[0] -= 5.0;
			position[1] -= 5.0;
		} else {
			x1 += 5.0;
			x2 += 5.0;
			position[0] += 5.0;
			position[1] += 5.0;
		}
	// Normal movements
	} else {
		// Move Zero horizontally
		if(buttons[RUN]){
			if(direction == LEFT){
				x1 -= 2.0;
				x2 -= 2.0;
				position[0] -= 2.0;
				position[1] -= 2.0;
			} else {
				x1 += 2.0;
				x2 += 2.0;
				position[0] += 2.0;
				position[1] += 2.0;
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
				position[2] -= 22.0;
				position[3] -= 22.0;
			} else {
				// Move Zero up
				y1 += 22.0;
				y2 += 22.0;
				position[2] += 22.0;
				position[3] += 22.0;
			}
		}
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
	if(y1 != 65.0){
		y1 -= 5.0;
		y2 -= 5.0;
	} else {
		if(counter % 5 == 0){
			// go to next frame
			x1_tcoord += x_offset;
			if(x1_tcoord >= 1.0){
				// Reset x frame pointer
				x1_tcoord = 0.0;
				// Move down 1 row
				y2_tcoord -= y_offset;
				// When Finished, load stand
				if(y2_tcoord <= 0.0){
					// Go into standing state
					state = STAND;
					// Resets coordinates
					x1 = 443.0;
					x2 = 494.2;
					y1 = 99.0;
					y2 = 163.0;
					resetTexture();
				}
			}
		}
	}
	counter++;
	// Resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Zero standing Animation
void Zero::stand()
{
	// How many frames to jump
	float x_offset = 0.1;
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
		if(x1_tcoord >= 1.0){
			x1_tcoord = 0.0;
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Zero saber attack Animation
void Zero::saber()
{

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
		position[0] = x2 - 21.8;
		position[1] = x2 + 8.8;
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[RUN_LEFT]); // select the active texture
		// Readjust cannon position
		position[0] = x1 - 8.8;
		position[1] = x1 + 21.8;
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
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
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
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Zero Fire Animation
void Zero::fire()
{
	// How many frames to jump
	float x_offset = 0.1666666666666666666666666666;
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
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	// Want to draw 5 frames per second
	if(counter % 8 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 1.0){
			x1_tcoord = 0.0;
			y2_tcoord -= y_offset;
			if(y2_tcoord <= 0){
				resetTexture();
				state = STAND;
				buttons[FIRE] = false;
			}
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
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
				buttons[DASH] = false;
				y2_tcoord = 1.0;
			}
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Responses
// Zero damage animation
void Zero::damage()
{

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
	loadDash();
	loadDamage();
	loadDie();
}

// Load Zero's Entry texture
void Zero::loadEntry()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Zero/Entry/Zero_Entry.png",
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
}

// Load Zero's Saber slash texture
void Zero::loadSaber()
{

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
}

// Load Zero's Damage texture
void Zero::loadDamage()
{

}

// Load Zero's Death texture
void Zero::loadDie()
{

}