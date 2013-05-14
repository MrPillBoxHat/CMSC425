/******************************************************
* Header file for Megaman X
*	Contains all function definitions
*   and state of the character
*******************************************************/
#pragma once

#include "BackGround.h"
#include "Zero.h"

class X {
	// Contains X's health and location
	private:
		float x1,x2,y1,y2; // location of X
		float position[4]; // location of cannon
		float hit_box[4];
		float health_location[4];
		int health;
		bool health_blocks[28];
		bool invinciple;
		int state;
		int direction; // X facing direction
		int counter; // FPS controller
		int count; // Frame Reset counter
		int count2; // Invincibility time
		float x1_tcoord; // texture x1 coord
		float y2_tcoord; // texture y2 coord
		GLuint textures[24]; // stores texture
		bool buttons[9]; // keeps track of state (buttons pressed)
		bool falling; // Check if X is falling
		bool onGround;
		int frame_count;
		bool play_3frame;
		BackGround *bg; // keeps track of environment

		// Private helper functions
		// helper functions to load textures
		void loadEntry();
		void loadStand();
		void loadMove();
		void loadJump();
		void loadSlide();
		void loadFire();
		void loadCharge();
		void loadDash();
		void loadDamage();
		void loadDie();
		void loadHealth();
		// Actions
		void entry();
		void stand();
		void run();
		void jump();
		void slide();
		void air_fire();
		void ground_fire();
		void charge();
		void dash();
		// Responses
		void damage();
		void die();
		// Move X's coordinates
		void move();
		// helper function to control movement
		void jump_move(float groundY);
		void move_horizontal(float distance);
		void move_vertical(float distance);
		void detec_ground(Rectangle2D **temp);
		void ifLand(float groundY);
		// Draw X's health bar
		void drawHealth();
		void gainHealth(int block_number);

	// Contains public functions
	public:
		// Contructor
		X(BackGround *inBG);
		// getters
		int getState(){return state;}
		int getDirection(){return direction;}
		int getHealth(){return health;}
		float *getCannon(){return position;}
		float *getHitBox(){return hit_box;}
		float getStart() const {return x1; }
		int middle() const { return x1 + (x2 - x1) / 2; }

		bool ifInvinciple(){return invinciple;}
		// setters
		void setHealth(int number){health += number;}
		void setState(int inState){state = inState; buttons[inState] = true;}
		void setDirection(int inDirection){direction = inDirection;}
		void setButtons(int button, bool boolean){buttons[button] = boolean;}
		void resetTexture(){x1_tcoord = 0.0; y2_tcoord = 1.0;}
		void setFrameOn(){play_3frame = true; frame_count = 1;}
		void setHitBox(float xx1, float xx2, float yy1, float yy2);
		void setPosition(float xx1, float xx2, float yy1, float yy2);
		void setFalling(){falling = true; x1_tcoord = 0.63;}
		void setOffGround(){onGround = false;}
		// Draw X
		void draw();
		// Loads all textures
		void loadTextures();
		// When x takes damage
		void depleteHealth(int block_number);
		void detec_collision(Zero *zero);
		void move_health(float distanceX1, float distanceX2);
};