#include "Saber.h"

// Constructor (missile)
Saber::Saber(float *position, int inDirection)
{
	x1 = position[0]-70.0;
	x2 = position[1]-30.0;
	y1 = position[2] + 25;
	y2 = position[3] + 25;
	float xmid = x1 + ((x2-x1)/2);
	float ymid = y1 + ((y2-y1)/2);
	hit_box[0] = xmid - 30.0;
	hit_box[1] = xmid + 30.0;
	hit_box[2] = ymid - 25.0;
	hit_box[3] = ymid + 25.0;
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	damage = -15;
	direction = inDirection;
}

// Constructor (saber)
Saber::Saber(float *position, int direction, int i)
{
	x1 = position[0]-70.0;
	x2 = position[1]-30.0;
	y1 = position[2];
	y2 = position[3];
	float xmid = x1 + ((x2-x1)/2);
	float ymid = y1 + ((y2-y1)/2);
	if(direction == LEFT){
		hit_box[0] = xmid - 130.0;
		hit_box[1] = xmid - 10.0;
		hit_box[2] = ymid - 50.0;
		hit_box[3] = ymid + 40.0;
	} else {
		hit_box[0] = xmid + 75.0;
		hit_box[1] = xmid + 173.0;
		hit_box[2] = ymid - 55.0;
		hit_box[3] = ymid + 60.0;
	}
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	damage = -25;
}

// Draw saber missile
void Saber::draw(GLuint *texture)
{
	// How many frames to jump
	float x_offset = 0.125;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == LEFT){
		glBindTexture(GL_TEXTURE_2D, texture[Z_SABER_LEFT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, texture[Z_SABER_RIGHT]); // select the active texture
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
		x1 -= 11.5;
		x2 -= 11.5;
		hit_box[0] -= 11.5;
		hit_box[1] -= 11.5;
	} else {
		x1 += 11.5;
		x2 += 11.5;
		hit_box[0] += 11.5;
		hit_box[1] += 11.5;
	}
	y1 += 5.0;
	y2 += 5.0;
	hit_box[2] += 5.0;
	hit_box[3] += 5.0;
	// update next frame or reset if reached the end
	x1_tcoord += x_offset;
	if(x1_tcoord >= 1.0){
		x1_tcoord = 0.0;
	}
}

bool Saber::collision(X *x)
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