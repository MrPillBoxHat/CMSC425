/******************************************************
* Megaman X Class
*	Contains all function implementations
*   and actions of the character
*******************************************************/

#include <iostream>						// input/outout stream
#include <cstdlib>						// C++ standard definitions
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL
#include "SOIL.h" 						// Library for loading images
#include "X.h" 							// X header file

using namespace std;

// Contructor
X::X()
{
	health = 50;
	// Coordinates of entry
	x1 = 305.0;
	x2 = 433.0;
	y1 = 500.0;
	y2 = 628.0;
	// Cannon position after entry animation
	position[0] = 377.4;
	position[1] = 408.0;
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
	bool play_3frame = false;
	int frame_count = 1;
}

/***************************************************************************************************
* Draw function
*	draws the main character X depending on his state
*	Uses helper functions to draw each state
*
****************************************************************************************************/
void X::draw()
{
	// Move X in the world
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
			// if in the air
			if(buttons[JUMP]){
				buttons[FIRE] = false;
				state = JUMP;
				jump();
				/*// Match jump frame with jump fire frame
				x1_tcoord *= 2;
				// If texture pointer is past 0.5, subtract 0.5
				if(x1_tcoord >= 0.5){
					x1_tcoord -= 0.5;
					y2_tcoord = 0.5;
				}
				air_fire();*/
			} else {
				ground_fire();
			}
			break;
		case CHARGE:
			charge();
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

// Moves X in the world
void X::move()
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
		// Move X horizontally
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
	// Move X vertically
	if(buttons[JUMP]){
		// FPS control
		if(counter %5 == 0){
			// If firing in the air
			if(buttons[FIRE] && buttons[JUMP]){
				if(x1_tcoord >= .27 && y2_tcoord == 0.5){
					// no change in position
				} else if ((y2_tcoord == 0.5 && x1_tcoord < .27) || 
						   (y2_tcoord == 1.0 && x1_tcoord >= .27)){
					// X is falling back down
					y1 -= 22.0;
					y2 -= 22.0;
					position[2] -= 22.0;
					position[3] -= 22.0;
				} else {
				// Move X up
					y1 += 22.0;
					y2 += 22.0;
					position[2] += 22.0;
					position[3] += 22.0;
				}
			// If normal jump
			} else {
				if(x1_tcoord >= 0.72){
				// no change in position
				} else if(x1_tcoord >= 0.36 && x1_tcoord < 0.72){
				// X is falling back down
					y1 -= 22.0;
					y2 -= 22.0;
					position[2] -= 22.0;
					position[3] -= 22.0;
				} else {
					// Move X up
					y1 += 22.0;
					y2 += 22.0;
					position[2] += 22.0;
					position[3] += 22.0;
				}
			}
		}
	}
}

/*************************************************************************************************
*  All helper functions that draw X's actions based on his state
*
*************************************************************************************************/
// Draws X entering the stage
void X::entry()
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
	// If X has not landed
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
					x1 = 338.0;
					x2 = 389.2;
					y1 = 99.0;
					y2 = 163.0;
					resetTexture();
				}
			}
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Draws X standing
void X::stand()
{
	// How many frames to jump
	float x_offset = 0.2;
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

// Draws X running
void X::run()
{
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

// Draws X jumping
void X::jump()
{
	// How many frames to jump
	float x_offset = 0.09090909090909090909;
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
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Draws X firing in the air
void X::air_fire()
{
	// How many frames to jump
	float x_offset;
	float y_offset = 0.5;
	// Move up one frame
	if(frame_count <= 3){
		x_offset = 0.04545454545454545454545;
		frame_count++;
	// Jump two frames
	} else {
		play_3frame = false;
		x_offset = 0.09090909090909090909090;
	}
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[JUMP_FIRE_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[JUMP_FIRE_LEFT]); // select the active texture
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
		if(x1_tcoord >= 0.5){
			x1_tcoord -= 0.5;
			y2_tcoord -= y_offset;
			if(y2_tcoord < 0){
				state = STAND;
				buttons[FIRE] = false;
				buttons[JUMP] = false;
				play_3frame = false;
			}
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Draws X firing on the ground
void X::ground_fire()
{
	// How many frames to jump
	float x_offset = 0.111111111111111111111111;
	float y_offset = 1.0;
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
	if(counter % 3 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 1.0){
			x1_tcoord = 0.0;
			state = STAND;
			buttons[FIRE] = false;
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

void X::charge()
{

}

// Draws and makes X perform a dash
void X::dash()
{
	// How many frames to jump
	float x_offset = 0.125;
	float y_offset = 1.0;
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
			// If player is holding move change to run
			if(buttons[RUN]){
				x1_tcoord = 0.375;
				state = RUN;
			// If player is not holding move, change to stand
			} else {
				x1_tcoord = 0.0;
				state = STAND;
			}
			buttons[DASH] = false;
		}
	}
	counter++;
	//resets counter
	if(counter == 60){
		counter = 0;
	}
}

// Responses
void X::damage()
{

}
void X::die()
{

}

/***********************************************************************************************
* loadTextures()
*	Creates and loads all textures onto the video card
*	Uses smaller helper functions to load all the images to make code more readable
*	Each state has two images, one for facing left and one for facing right.
*
***********************************************************************************************/
void X::loadTextures()
{
	loadEntry();
	loadStand();
	loadMove();
	loadJump();
	loadFire();
	loadCharge();
	loadDash();
	loadDamage();
	loadDie();
}

/***************************************************************************************************
* loadXXXX()
*	loads specific images related to the function name
*	These are helper functions used in order to make code more organized and readable
*
***************************************************************************************************/
// Loads entry images
void X::loadEntry()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/Entry/X_Entry.png",
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

	cout << "textureID: " << textureID << endl;

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

// Loads standing images
void X::loadStand()
{
	/* loads stand right image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/stand/stand_right.png",
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

	cout << "textureID: " << textureID << endl;

	textures[STAND_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads stand left image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/stand/stand_left.png",
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

	cout << "textureID: " << textureID << endl;

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

// Loads running images
void X::loadMove()
{
	/* loads move right image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/Run/run_right.png",
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

	cout << "textureID: " << textureID << endl;

	textures[RUN_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads stand left image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/Run/run_left.png",
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

	cout << "textureID: " << textureID << endl;

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

// Loads jumping images
void X::loadJump()
{
	/* loads jump right image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/jump/jump_right.png",
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

	cout << "textureID: " << textureID << endl;

	textures[JUMP_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads jump left image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/jump/jump_left.png",
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

	cout << "textureID: " << textureID << endl;

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

// Loads firing images
void X::loadFire()
{
	/* loads jump right image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/fire/ground/fire_right.png",
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

	cout << "textureID: " << textureID << endl;

	textures[FIRE_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads jump left image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/fire/ground/fire_left.png",
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

	cout << "textureID: " << textureID << endl;

	textures[FIRE_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads jump left image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/fire/air/fire_right.png",
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

	cout << "textureID: " << textureID << endl;

	textures[JUMP_FIRE_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads jump left image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/fire/air/fire_right.png",
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

	cout << "textureID: " << textureID << endl;

	textures[JUMP_FIRE_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Loads charging images
void X::loadCharge()
{

}

// Loads dashing images
void X::loadDash()
{
	/* loads jump right image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/dash/dash_right.png",
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

	cout << "textureID: " << textureID << endl;

	textures[DASH_RIGHT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads jump left image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/dash/dash_left.png",
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

	cout << "textureID: " << textureID << endl;

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

// Loads damage (getting hit) images
void X::loadDamage()
{

}

// Load death image
void X::loadDie()
{

}