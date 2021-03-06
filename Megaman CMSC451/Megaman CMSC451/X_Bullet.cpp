#include "X_Bullet.h"

// Constructor
X_Bullet::X_Bullet(float *position, int inDirection, BackGround *inbg)
{
	x1 = position[0];
	x2 = position[1];
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
	damage = -5;
	state = 0;
	direction = inDirection;
	counter = 0;
	bg = inbg;
}

// Constructor for charge bullet
X_Bullet::X_Bullet(float *position, int inDirection, int filler, BackGround *inbg)
{
	x1 = position[0] - 50.0;
	x2 = position[1] + 50.0;
	y1 = position[2];
	y2 = position[3];
	float xmid = x1 + ((x2-x1)/2);
	float ymid = y1 + ((y2-y1)/2);
	hit_box[0] = xmid - 50.0;
	hit_box[1] = xmid + 50.0;
	hit_box[2] = ymid - 40.0;
	hit_box[3] = ymid + 40.0;
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	damage = -20;
	state = 0;
	direction = inDirection;
	counter = 0;
	bg = inbg;
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
	if(state != DIE){
		move();
	}
	// update next frame or reset if reached the end
	// Control FPS
	x1_tcoord += x_offset;
	if(state == DIE){
		if(counter % 60 == 0){
			if(x1_tcoord >= 0.984375){
				// Move bullet to where it will be deleted
				x1 = -100;
				x2 = -100;
			}
		}
	} else {
		if(x1_tcoord >= 0.984375){
			x1_tcoord = 0.0;
		}
	}
}

void X_Bullet::drawCharge(GLuint *texture)
{
	// How many frames to jump
	float x_offset = 0.25;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, texture[XCHARGE_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, texture[XCHARGE_LEFT]); // select the active texture
	}
	// Draw objects
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
		glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
		glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
	glEnd();
	if(state != DIE){
		if(direction == 0){
			// Move bullet
			x1 -= 12.0;
			x2 -= 12.0;
			hit_box[0] -= 12.0;
			hit_box[1] -= 12.0;
		} else {
			x1 += 12.0;
			x2 += 12.0;
			hit_box[0] += 12.0;
			hit_box[1] += 12.0;
		}
	}
	// update next frame or reset if reached the end
	// Control FPS
	x1_tcoord += x_offset;
	if(state == DIE){
		// Move bullet to where it will be deleted
		x1 = -100;
		x2 = -100;
	} else {
		if(x1_tcoord >= 0.9){
			x1_tcoord = 0.0;
		}
	}
}

void X_Bullet::move()
{
	// If facing LEFT
	if(direction == LEFT){
		if(bg->canMove(hit_box[0] - 12.0, hit_box[2], hit_box[1] - 12.0, hit_box[3])){
			// Move bullet
			auxMove(-12.0);
		} else {
			state = DIE;
		}
	} else {
		if(bg->canMove(hit_box[0] + 12.0, hit_box[2], hit_box[1] + 12.0, hit_box[3])){
			// Move bullet
			auxMove(-12.0);
		} else {
			state = DIE;
		}
	}
}

void X_Bullet::auxMove(float distance)
{
	x1 += distance;
	x2 += distance;
	hit_box[0] += distance;
	hit_box[1] += distance;
}

bool X_Bullet::collision(Zero *zero)
{
	// Get Zero's Position
	float *position = zero->getHitBox();
	// boolean flags to check where the bullet lies
	bool withinSides = hit_box[1] >= position[0] && hit_box[0] <= position[1];
	bool withinTopBottom = hit_box[2] <= position[3] && hit_box[3] >= position[2];
	// Check if the bullet touches Zero
	if(withinSides && withinTopBottom){
		state = DIE;
		return true;
	}
	return false;
}