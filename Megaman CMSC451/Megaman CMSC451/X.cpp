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

// Enumerations
enum directions {LEFT, RIGHT};
enum states {STAND, MOVE, JUMP, FIRE, CHARGE, DASH, DAMAGE, DIE};

// Contructor
X::X()
{
	health = 50;
	x_coordinate = 0.0;
	y_coordinate = 0.0;
	state = STAND;
	direction = RIGHT;
}

// Draw X
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

// Actions
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	GL_LINEAR_MIPMAP_LINEAR);
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