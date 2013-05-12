/******************************************************
* Header file for Megaman X
*	Contains all function definitions
*   and state of the character
*******************************************************/
#pragma once

#include <GL\glut.h>
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
		int state;
		int direction; // X facing direction
		int counter; // FPS controller
		int count; // Frame Reset counter
		float x1_tcoord; // texture x1 coord
		float y2_tcoord; // texture y2 coord
		GLuint textures[22]; // stores texture
		bool buttons[9]; // keeps track of state (buttons pressed)
		int frame_count;
		bool play_3frame;

		// Private helper functions
		// helper functions to load textures
		void loadEntry();
		void loadStand();
		void loadMove();
		void loadJump();
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
		void air_fire();
		void ground_fire();
		void charge();
		void dash();
		// Responses
		void damage();
		void die();
		// Move X's coordinates
		void move();
		// Draw X's health bar
		void drawHealth();
		void gainHealth(int block_number);

	// Contains public functions
	public:
		// Contructor
		X();
		// getters
		int getState(){return state;}
		int getDirection(){return direction;}
		int getHealth(){return health;}
		float *getCannon(){return position;}
		float *getHitBox(){return hit_box;}
		// setters
		void setHealth(int number){health += number;}
		void setState(int inState){state = inState; buttons[inState] = true;}
		void setDirection(int inDirection){direction = inDirection;}
		void setXPosition(float inx1, float inx2){x1 += inx1; x2 += inx2;}
		void setButtons(int button, bool boolean){buttons[button] = boolean;}
		void resetTexture(){x1_tcoord = 0.0; y2_tcoord = 1.0;}
		void setFrameOn(){play_3frame = true; frame_count = 1;}
		void setHitBox(float xx1, float xx2, float yy1, float yy2);
		// Draw X
		void draw();
		// Loads all textures
		void loadTextures();
		// When x takes damage
		void depleteHealth(int block_number);
		void detec_collision(Zero *zero);
};