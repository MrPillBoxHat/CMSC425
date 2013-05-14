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
#include "constants.h"
#include "Sound.h"
using namespace std;
Sound *sound = new Sound();
bool ifPlayed = false;

// Contructor
X::X(BackGround *inBG)
{
	health = 140;
	// Coordinates of entry
	x1 = 280.0;
	x2 = 458.0;
	y1 = 490.0;
	y2 = 728.0;
	// Cannon position after entry animation
	position[0] = 352.4;
	position[1] = 433.0;
	position[2] = 89.0;
	position[3] = 176.0;
	// Hit box for X
	hit_box[0] = 325.0;
	hit_box[1] = 407.2;
	hit_box[2] = 76.0;
	hit_box[3] = 155.0;
	health_location[0] = 28.0;
	health_location[1] = 100.0;
	health_location[2] = 231.0;
	health_location[3] = 607.0;
	// Initialize X's state
	state = ENTRY;
	x1_tcoord = 0.0;
	y2_tcoord = 1.0;
	direction = RIGHT;
	counter = 0; // Counter is to keep track of FPS
	count = 0; // Frame controller
	count2 = 0; // Invincibility Time
	invinciple = false; // Determine whether X can take damage
	bg = inBG;
	falling = false; // X is not falling
	onGround = true;
	dashed = false;
	// Initialize health blocks and buttons pressed
	for(int i = 0; i < 9; i++){
		buttons[i] = false;
		health_blocks[i] = true;
	}
	for(int i = 9; i < 28; i++){
		health_blocks[i] = true;
	}
	bool play_3frame = false;
	int frame_count = 1;
}

// Sets up hitbox
void X::setHitBox(float xx1, float xx2, float yy1, float yy2)
{
	hit_box[0] += xx1;
	hit_box[1] += xx2;
	hit_box[2] += yy1;
	hit_box[3] += yy2;
}

// Sets up texture box
void X::setPosition(float xx1, float xx2, float yy1, float yy2)
{
	x1 += xx1;
	x2 += xx2;
	y1 += yy1;
	y2 += yy2;
}

// Detecs collision with enemy
void X::detec_collision(Zero *zero)
{
	float *z_hitbox = zero->getHitBox();
	bool withinSides = hit_box[1] >= z_hitbox[0] && hit_box[0] <= z_hitbox[1];
	bool withinTopBottom = hit_box[2] <= z_hitbox[3] && hit_box[3] >= z_hitbox[2];
	if(withinSides && withinTopBottom){
		sound->xPlayHurtSFX();
		setButtons(DASH, false);
		// Get out of dash animation and stop moving
		if(state == DASH){
			if(direction == RIGHT){
				setHitBox(0.0, -8.0, 0.0, 12.0);
			} else {
				setHitBox(8.0, 0.0, 0.0, 12.0);
			}
		} else if (state == RUN) {
			buttons[RUN] = false;
		}
		resetTexture();
		setState(DAMAGE);
		health -= 10;
		depleteHealth(health/5);
	}
}

// Moves X in the world
void X::move()
{
	// Dash movement (faster movement)
	if(buttons[DASH]){
		// Move only if at the correct frame or if state is jump
		if(x1_tcoord < 0.5 || state == JUMP){
			if(direction == LEFT){
				// Check if possible to move left
				if(bg->canMove(hit_box[0] - CM_DASH, hit_box[3])){
					move_horizontal(CM_DASH * -1);
				} else {
					x1_tcoord = 0.5;
				}
			} else {
				// Check if possible to move right
				if(bg->canMove(hit_box[1] + CM_DASH, hit_box[3])){
					move_horizontal(CM_DASH);
				} else {
					x1_tcoord = 0.5;
				}
			}
		}
	// Normal movements
	} else {
		 if (state == JUMP_OUT){
			if(direction == LEFT){
				//move out right
				move_horizontal(CM_WALK);
			} else {
				//move out left
				move_horizontal(CM_WALK * -1);
			}
			move_vertical(10.0);
		 // Move X horizontally
		 } else if(buttons[RUN]){
			if(direction == LEFT){
				// Check if possible to move left
				if(bg->canMove(hit_box[0] - CM_WALK, hit_box[3])){
					move_horizontal(CM_WALK * -1);
				// change state to wall slide
				} else if (state != SLIDE && state == JUMP && !onGround) {
					state = SLIDE;
					if(direction == LEFT){
						setHitBox(-20.0, -20.0, 0.0, 0.0);
						setPosition(-20.0, -20.0, 0.0, 0.0);
					}
					resetTexture();
				}
			} else {
				// Check if possible to move right
				if(bg->canMove(hit_box[1] + CM_WALK, hit_box[3])){
					move_horizontal(CM_WALK);
				// change state to wall slide
				} else if (state != SLIDE && state == JUMP && !onGround) {
					// change state to wall slide
					state = SLIDE;
					setHitBox(20.0, 20.0, 0.0, 0.0);
					setPosition(20.0, 20.0, 0.0, 0.0);
					resetTexture();
				}
			}
		}
	}
	// check if there is still ground underneath
	Rectangle2D *temp;
	float groundY = 0.0;
	detec_ground(&temp);
	// If nothing was returned, X will fall
	if(temp == nullptr){
		setFalling();
		onGround = false;
		setState(JUMP);
	} else {
		groundY = temp->getMaxY();
	}
	//if Sliding down a wall
	if (state == SLIDE) {
		move_vertical(-0.7);
		ifLand(groundY);
	// Move X vertically
	} else if(buttons[JUMP]){
		jump_move(groundY);
	}
}

//helper function to move x while in jump state
void X::jump_move(float groundY)
{
	// If firing in the air
	//if(buttons[FIRE]){
		
	// If normal jump
	//} else {
		if(falling){
			move_vertical(-5.0);
			ifLand(groundY);
		} else if(!onGround) {
			// Move X up if not on landing frame
			move_vertical(5.0);
		}	
	//}
}

void X::move_horizontal(float distance)
{

	x1 += distance;
	x2 += distance;
	position[0] += distance;
	position[1] += distance;
	hit_box[0] += distance;
	hit_box[1] += distance;
}

void X::move_vertical(float distance)
{

	y1 += distance;
	y2 += distance;
	position[2] += distance;
	position[3] += distance;
	hit_box[2] += distance;
	hit_box[3] += distance;
}

void X::detec_ground(Rectangle2D **temp)
{
	if(direction == LEFT){
		*temp = bg->getBelow(hit_box[1],hit_box[2]);
	} else {
		*temp = bg->getBelow(hit_box[0], hit_box[2]);
	}
}

void X::move_health(float distanceX, float distanceY)
{
	health_location[0] = distanceX + 28;
	health_location[1] = distanceX + 100;
	//health_location[2] += distanceY;
	//health_location[3] += distanceY;
}

void X::ifLand(float groundY)
{
	if(y1 <= groundY){
		float difference = (groundY - y1);
		x1_tcoord = 0.81;
		falling = false;
		onGround = true;
		if(state == SLIDE){
			if(direction == LEFT){
				setHitBox(20.0, 20.0, 0.0, 0.0);
				setPosition(20.0, 20.0, 0.0, 0.0);
			} else {
				setHitBox(-20.0, -20.0, 0.0, 0.0);
				setPosition(-20.0, -20.0, 0.0, 0.0);
			}
		}
		state = JUMP;
		hit_box[2] += difference;
		hit_box[3] += difference;
		position[2] += difference;
		position[3] += difference;
		y1 += difference;
		y2 += difference;
		dashed = false;
	}
}

/**************************************************************************************************
* Draw health() functions
*	Draw X's life.  Increase and decrease base on damage taken
*   and items retrived
**************************************************************************************************/
// Draws Zero's Health bar
void X::drawHealth()
{
	// Draw the bar
	glBindTexture(GL_TEXTURE_2D, textures[HEALTH_BAR]); // select the active texture
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(0.0, 0.0); glVertex2d(health_location[0], health_location[2]);
		glTexCoord2d(1.0, 0.0); glVertex2d(health_location[1], health_location[2]);
		glTexCoord2d(1.0, 1.0); glVertex2d(health_location[1], health_location[3]);
		glTexCoord2d(0.0, 1.0); glVertex2d(health_location[0], health_location[3]);
	glEnd();
	// Draw the blocks
	glBindTexture(GL_TEXTURE_2D, textures[HEALTH_BLOCK]); // select the active texture
	// position of health blocks
	float xx1 = health_location[0] + 12.0;
	float xx2 = health_location[1] - 17.0;
	float yy1 = health_location[2] + 101.0;
	float yy2 = health_location[2] + 116.0;
	int i = 0; // counter to iterate through health_blocks
	// iterate through the blocks and draw them
	while(i < 28 && health_blocks[i]){
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(0.0, 0.0); glVertex2d(xx1, yy1);
			glTexCoord2d(1.0, 0.0); glVertex2d(xx2, yy1);
			glTexCoord2d(1.0, 1.0); glVertex2d(xx2, yy2);
			glTexCoord2d(0.0, 1.0); glVertex2d(xx1, yy2);
		glEnd();
		yy1 += 8.0;
		yy2 += 8.0;
		i++; // increment count
	}
}

// Draws the animation that fills Zero's health
void X::gainHealth(int block_number)
{
	// iterate through health bar
	for(int i = 0; i < 28; i++){
		// if the bar is not there
		if(!health_blocks[i]){
			// draw the bar
			health_blocks[i] = true;
			break;
		}
	}
}

// Decreases the amount of health blocks
void X::depleteHealth(int block_number)
{
	if(!invinciple){
		// start at the end of the array
		int i = 27;
		// sets all health blocks to false
		while(i >= block_number){
			if(health_blocks[i]){
				health_blocks[i] = false;
			}
			i--;
		}
	}
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
	if(state != ENTRY && state != DAMAGE){
		move();
	}
	// Draws X's health
	if(state != ENTRY){
		drawHealth();
	}
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
		case JUMP_OUT:
			jumpOut();
			break;
		case SLIDE:
			slide();
			break;
		case FIRE:
			// if in the air
			if(buttons[JUMP]){
				// set fire to false
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
			invinciple = true;
			damage();
			break;
		case DIE:
			die();
			break;
	}
	counter++;
	// resets counter
	if(counter == 60){
		counter = 0;
	}
	// Keeps track of invinciple time
	if(invinciple){
		if(count2++ == 110){
			count2 = 0;
			invinciple = false;
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
	if(y1 > 10.0){
		y1 -= 13.0;
		y2 -= 13.0;
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
					x1 = 317.0;
					x2 = 418.2;
					y1 = 74.0;
					y2 = 188.0;
					resetTexture();
				}
			}
		}
	}
}

// Draws X standing
void X::stand()
{
	// How many frames to jump
	float x_offset = 0.099609375;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[STAND_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[STAND_LEFT]); // select the active texture
	}
	//create flicker effect
	if(count2 % 2 == 0){
		// Draw objects
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
			glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
		glEnd();
	}
	// Want to draw 5 frames per second
	if(counter % 10 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 0.99609375){
			x1_tcoord = 0.0;
		}
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
		position[0] = x2 - 25.0;
		position[1] = x2 + 50.0;
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[RUN_LEFT]); // select the active texture
		// Readjust cannon position
		position[0] = x1 - 50.0;
		position[1] = x1 + 25.0;
	}
	//create flicker effect
	if(count2 % 2 == 0){
		// Draw objects
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
			glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
		glEnd();
	}
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
	//create flicker effect
	if(count2 % 2 == 0){
		// Draw objects
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
			glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
		glEnd();
	}
	// Update frame pointers
	if(counter % 5 == 0){
		// increment offset if not in fall frame
		if(x1_tcoord < 0.62 || x1_tcoord >= 0.81) {
			x1_tcoord += x_offset;
		}
		//if on land frame play sound
		if(x1_tcoord >= 0.81 && ifPlayed == false){	
			sound->playLandSFX();
			onGround = true;
			ifPlayed = true;
			falling = false;
		// If X reaches a certain frame, he begins falling
		} else if(x1_tcoord >= 0.54 && x1_tcoord < 0.81){
			falling = true;
		}
		// When finished playing
		if(x1_tcoord >= 0.99){
			if(buttons[RUN]){
				state = RUN;
				x1_tcoord = 0.0;
				y2_tcoord = 0.5;
			} else {
				// Reset state
				x1_tcoord = 0.0;
				state = STAND;
			}
			ifPlayed = false;
			buttons[JUMP] = false;
			buttons[DASH] = false;
		}
	}
}

void X::jumpOut()
{
	// How many frames to jump
	float x_offset;
	if(x1_tcoord == 0.0){
		x_offset = 0.25;
	} else {
		x_offset = 0.090909090909090909;
	}
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		if(x1_tcoord == 0.0){
			glBindTexture(GL_TEXTURE_2D, textures[SLIDE_RIGHT]); // select the active texture
		} else {
			glBindTexture(GL_TEXTURE_2D, textures[JUMP_RIGHT]); // select the active texture
		}
	} else {
		if(x1_tcoord == 0.0){
			glBindTexture(GL_TEXTURE_2D, textures[SLIDE_LEFT]); // select the active texture
		} else {
			glBindTexture(GL_TEXTURE_2D, textures[JUMP_LEFT]); // select the active texture
		}
	}
	//create flicker effect
	if(count2 % 2 == 0){
		// Draw objects
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
			glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
		glEnd();
	}
	// Want to draw 5 frames per second
	x_offset = 0.090909090909090909;
	//update next frame or reset if reached the end
	x1_tcoord += x_offset;
	if(x1_tcoord >= 0.54 && x1_tcoord < 0.81){
		falling = true;
		state = JUMP;
	}
}

// Draws X sliding down a wall
void X::slide()
{
	// How many frames to jump
	float x_offset = 0.25;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[SLIDE_RIGHT]); // select the active texture
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[SLIDE_LEFT]); // select the active texture
	}
	//create flicker effect
	if(count2 % 2 == 0){
		// Draw objects
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
			glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
		glEnd();
	}
	// Want to draw 5 frames per second
	if(counter % 5 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 0.99609375){
			x1_tcoord = 0.75;
		}
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
}

// Draws X firing on the ground
void X::ground_fire()
{
	// How many frames to jump
	float x_offset = 0.109375;
	float y_offset = 1.0;
	// Readjust where X is being drawn
	float xx1;
	float xx2;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[FIRE_RIGHT]); // select the active texture
		xx1 = x1 + 5.0;
		xx2 = x2 + 5.0;
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[FIRE_LEFT]); // select the active texture
		xx1 = x1 - 5.0;
		xx2 = x2 - 5.0;
	}
	//create flicker effect
	if(count2 % 2 == 0){
		// Draw objects
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(xx1, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(xx2, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(xx2, y2);
			glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(xx1, y2);
		glEnd();
	}
	// Want to draw 5 frames per second
	if(counter % 3 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		if(x1_tcoord >= 0.984375){
			x1_tcoord = 0.0;
			state = STAND;
			buttons[FIRE] = false;
		}
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
	//create flicker effect
	if(count2 % 2 == 0){
		// Draw objects
		glBegin(GL_POLYGON);
			//real coord
			glTexCoord2d(x1_tcoord, y2_tcoord - y_offset);  glVertex2d(x1, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord - y_offset); glVertex2d(x2, y1);
			glTexCoord2d(x1_tcoord + x_offset, y2_tcoord); glVertex2d(x2, y2);
			glTexCoord2d(x1_tcoord, y2_tcoord); glVertex2d(x1, y2);
		glEnd();
	}
	// Want to draw 5 frames per second
	if(counter % 3 == 0){
		//update next frame or reset if reached the end
		x1_tcoord += x_offset;
		// Resets frame to play again
		if(x1_tcoord >= 0.5 && count < 4){
			count++;
			x1_tcoord = 0.375;
		}
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
			// Reset hitbox
			count = 0;
			if(direction == RIGHT){
				setHitBox(0.0, -8.0, 0.0, 12.0);
			} else {
				setHitBox(8.0, 0.0, 0.0, 12.0);
			}
			if(!onGround){
				state = JUMP;
				buttons[JUMP] = true;
				setFalling();
			}
			buttons[DASH] = false;
			// if X is still in the air, make him fall
			//setPosition(20.0, -20.0, 0.0, 10.0);
		}
	}
}

// Responses
void X::damage()
{
	// How many frames to jump
	float x_offset = 0.125;
	float y_offset = 1.0;
	// Draws the frame
	if(direction == RIGHT){
		glBindTexture(GL_TEXTURE_2D, textures[DAMAGE_RIGHT]); // select the active texture
		x1 += 0.1;
		x2 += 0.1;
		hit_box[0] += 0.1;
		hit_box[1] += 0.1;
	} else {
		glBindTexture(GL_TEXTURE_2D, textures[DAMAGE_LEFT]); // select the active texture
		x1 -= 0.1;
		x2 -= 0.1;
		hit_box[0] -= 0.1;
		hit_box[1] -= 0.1;
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
			if (buttons[JUMP]){
				state = JUMP;
				setFalling();
			} else {
				resetTexture();
				state = STAND;
			}
		}
	}
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
	loadSlide();
	loadFire();
	loadCharge();
	loadDash();
	loadDamage();
	loadDie();
	loadHealth();
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

// Loads sliding images
void X::loadSlide()
{
	/* loads jump right image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/slide/slide_right.png",
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

	cout << "XtextureID: " << textureID << endl;

	textures[SLIDE_RIGHT] = textureID; // Assign it to the texture array
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
		"Sprites/Megaman/slide/slide_left.png",
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

	textures[SLIDE_LEFT] = textureID; // Assign it to the texture array
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

// Load X's Health Bar texture
void X::loadHealth()
{
	/* loads entry image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/Health_bar/health_bar.png",
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

	cout << "XHealthTextureID: " << textureID << endl;

	textures[HEALTH_BAR] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textureID = SOIL_load_OGL_texture
	(
		"Sprites/health_block.png",
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

	textures[HEALTH_BLOCK] = textureID; // Assign it to the texture array
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
	/* loads jump right image directly as a new OpenGL texture */
	GLuint textureID = SOIL_load_OGL_texture
	(
		"Sprites/Megaman/damage/front/damage_right.png",
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

	cout << "XtextureID: " << textureID << endl;

	textures[DAMAGE_RIGHT] = textureID; // Assign it to the texture array
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
		"Sprites/Megaman/damage/front/damage_left.png",
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

	cout << "XtextureID: " << textureID << endl;

	textures[DAMAGE_LEFT] = textureID; // Assign it to the texture array
	glBindTexture(GL_TEXTURE_2D, textureID); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load death image
void X::loadDie()
{

}