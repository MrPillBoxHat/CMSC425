#include "Texture.h"
#include <SOIL.h>
#include <iostream>

using namespace std;

Texture::Texture(string fileName)
{
	/* loads move right image directly as a new OpenGL texture */
	id = SOIL_load_OGL_texture
	(
		fileName.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == id )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		cout << "File: " << fileName << endl;
		exit(0);
	}

	cout << "textureID: " << id << ", file: " << fileName << endl;

	glBindTexture(GL_TEXTURE_2D, id); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// default points
	tL = Point(0, 1);
	tR = Point(1, 1);
	bL = Point(0, 0);
	bR = Point(1, 0);
}

Texture::~Texture(void)
{
}

void Texture::setBoundary(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	setBottLeft(x1, y1);
	setBottRight(x2, y1);
	setTopLeft(x1, y2);
	setTopRight(x2, y2);
}