#include "Z_Bullet.h"
#include "X.h"
#include "constants.h"

// Constructor
Z_Bullet::Z_Bullet(float *position, int inDirection)
{
	x1 = position[0]-60.0;
	x2 = position[1]-20.0;
	y1 = position[2];
	y2 = position[3];
	float xmid = x1 + ((x2-x1)/2);
	float ymid = y1 + ((y2-y1)/2);
	hit_box[0] = xmid - 4.0;
	hit_box[1] = xmid + 4.0;
	hit_box[2] = ymid - 3.5;
	hit_box[3] = ymid + 3.5;
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	damage = -15;
	direction = inDirection;
	counter = 0;
}

void Z_Bullet::draw(GLuint *texture)
{
	// How many frames to jump
	float x_offset = 0.125;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == LEFT){
		glBindTexture(GL_TEXTURE_2D, texture[Z_BULLET_LEFT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, texture[Z_BULLET_RIGHT]); // select the active texture
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
		x1 -= 5.0;
		x2 -= 5.0;
		hit_box[0] -= 5.0;
		hit_box[1] -= 5.0;
	} else {
		x1 += 5.0;
		x2 += 5.0;
		hit_box[0] += 5.0;
		hit_box[1] += 5.0;
	}
	// update next frame or reset if reached the end
	counter++;
	if(counter % 7 == 0){
		x1_tcoord += x_offset;
		if(x1_tcoord >= 1.0){
			x1_tcoord = 0.625;
		}
	}
}

bool Z_Bullet::collision(X *x)
{
	// Get Zero's Position
	float *position = x->getHitBox();
	// boolean flags to check where the bullet lies
	bool withinSides = hit_box[1] >= position[0] && hit_box[0] <= position[1];
	bool withinTopBottom = hit_box[2] <= position[3] && hit_box[3] >= position[2];
	// Check if the bullet touches Zero
	if(withinSides && withinTopBottom){
		return true;
	}
	return false;
}