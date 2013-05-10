#include "X_Bullet.h"
#include "X.h"
#include "constants.h"

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
	state = 0;
	direction = inDirection;
	counter = 0;
}

void X_Bullet::draw(GLuint *texture)
{
	// How many frames to jump
	float x_offset;
	float y_offset = 1.0;
	// Draws the frame
	if(state != DIE){
		glBindTexture(GL_TEXTURE_2D, texture[XBULLET]); // select the active texture
		x_offset = 0.5;
	} else {
		glBindTexture(GL_TEXTURE_2D, texture[XBULLETDIE]); // select the active texture
		x_offset = 0.328125;
	}
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
		x1 -= 9.0;
		x2 -= 9.0;
	} else {
		x1 += 9.0;
		x2 += 9.0;
	}
	// update next frame or reset if reached the end
	// Control FPS
	x1_tcoord += x_offset;
	if(state == DIE){
		if(counter % 15 == 0){
			if(x1_tcoord >= 0.984375){
				x1_tcoord = 0.0;
			}
		}
	} else {
		if(x1_tcoord >= 0.984375){
			x1_tcoord = 0.0;
		}
	}
}
