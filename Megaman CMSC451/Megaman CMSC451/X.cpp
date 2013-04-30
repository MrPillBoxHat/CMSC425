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
#include <SOIL.h>						// Library for loading images
#include "X.h"							// X header file

/*********************************************************************************************
* Enumerations
*	Keeps track of the state of X and also creates symbols to make code easier to read 
*	and program
*
*********************************************************************************************/
enum directions {LEFT, RIGHT};
enum states {STAND, MOVE, JUMP, FIRE, CHARGE, DASH, DAMAGE, DIE};
enum texture_states{STAND_RIGHT, STAND_LEFT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT,
					FIRE_LEFT, FIRE_RIGHT, DASH_LEFT, DASH_RIGHT, DAMAGE_LEFT, DAMAGE_RIGHT,
					DIE_LEFT, DIE_RIGHT, CHARGE_TEXTURE};

// Contructor
X::X()
{
	health = 50;
	x_coordinate = 0.0;
	y_coordinate = 0.0;
	state = STAND;
	direction = RIGHT;
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
// Loads standing images
void X::loadStand()
{
	glGenTextures(1, &textures[STAND_RIGHT]);
	/* load an image file directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"stand_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		std::cout << "SOIL loading error:" << SOIL_last_result() << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	// (use GL_REPLACE below for skyboxes)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenTextures(1, &textures[STAND_RIGHT]);

	/* load an image file directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"stand_left.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		std::cout << "SOIL loading error:" << SOIL_last_result() << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	// (use GL_REPLACE below for skyboxes)
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

}

// Loads jumping images
void X::loadJump()
{

}

// Loads firing images
void X::loadFire()
{

}

// Loads charging images
void X::loadCharge()
{

}

// Loads dashing images
void X::loadDash()
{

}

// Loads damage (getting hit) images
void X::loadDamage()
{

}

// Load death image
void X::loadDie()
{

}

/***************************************************************************************************
* Draw function
*	draws the main character X depending on his state
*	Uses helper functions to draw each state
*
****************************************************************************************************/
void X::draw()
{
	switch(X::getState())
	{
		case STAND:
			stand();
			break;
		case MOVE:
			move();
			break;
		case JUMP:
			jump();
			break;
		case FIRE:
			fire();
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

/*************************************************************************************************
*  All helper functions that draw X's actions based on his state
*
*************************************************************************************************/
void X::stand()
{
	/* load an image file directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"stand_right.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textureID )
	{
		std::cout << "SOIL loading error:" << SOIL_last_result() << std::endl;
	}
	glEnable(GL_TEXTURE_2D); // enable texturing
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	// (use GL_REPLACE below for skyboxes)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBegin(GL_POLYGON); // draw the object(s)
		glNormal3f( ... ); // set the surface normal
		glTexCoord2f( ... ); // set texture coords
		glVertex3f( ... ); // draw vertex
	// ... (repeat for other vertices)
	glEnd();
	glDisable(GL_TEXTURE_2D); // disable texturing
}

void X::move()
{

}

void X::jump()
{

}

void X::fire()
{

}
void X::charge()
{

}
void X::dash()
{

}
// Responses
void X::damage()
{

}
void X::die()
{

}