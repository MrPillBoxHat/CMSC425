#include "X_Bullet.h"
#include "X.h"

// Constructor
X_Bullet::X_Bullet(float *position, int inDirection)
{
	x1 = position[0];
	x2 = position[1];
	y1 = position[2];
	y2 = position[3];
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	damage = 10;
	direction = inDirection;
}

void loadTexture()
{

}

void move()
{

}

void X_Bullet::draw(GLuint texture)
{
	// How many frames to jump
	float x_offset = 0.5;
	float y_offset = 1.0;
	// Draws the frame
	glBindTexture(GL_TEXTURE_2D, texture); // select the active texture
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	if(direction == 0){
		// Move bullet
		x1 -= 7.0;
		x2 -= 7.0;
	} else {
		x1 += 7.0;
		x2 += 7.0;
	}
	//update next frame or reset if reached the end
	x1_tcoord += x_offset;
	if(x1_tcoord >= 1.0){
		x1_tcoord = 0.0;
	}
}

void detec_collision()
{

}

