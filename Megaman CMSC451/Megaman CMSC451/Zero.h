/******************************************************
* Header file for Zero
*	Contains all function definitions
*   and state of the character
*******************************************************/
#pragma once
#include <GL\glut.h>

class Zero {
	// Contains Zero's health and location
	private:
		float x1,x2,y1,y2; // location of Zero
		float hit_box[4];
		float cannon_position[4]; // location of cannon
		int health;
		bool health_blocks[28];
		int state;
		int direction; // Zero facing direction
		int counter; // FPS controller
		int count; // keeps track of times frames reset
		float x1_tcoord; // texture x1 coord
		float y2_tcoord; // texture y2 coord
		GLuint textures[22]; // stores texture
		bool buttons[9]; // keeps track of state (buttons pressed)
		bool init_health;

		// Private helper functions
		// helper functions to load textures
		void loadEntry();
		void loadStand();
		void loadMove();
		void loadJump();
		void loadSaber();
		void loadFire();
		void loadDash();
		void loadHealth();
		void loadDamage();
		void loadDie();
		// Actions
		void entry();
		void stand();
		void run();
		void jump();
		void saber();
		void fire();
		void dash();
		// Responses
		void damage();
		void die();
		// Move Zero's coordinates
		void move();
		// Draw Zero's Health bar
		void drawHealth();
		void gainHealth(int block_number);

	// Contains public functions
	public:
		// Contructor
		Zero();
		// getters
		int getState(){return state;}
		int getDirection(){return direction;}
		int getHealth(){return health;}
		bool getInit(){return init_health;}
		float *getCannon(){return cannon_position;}
		float *getHitBox();
		float *getTextureCoord();
		// setters
		void setState(int inState){state = inState; buttons[inState] = true;}
		void setHealth(int amount){health += amount;}
		void setDirection(int inDirection){direction = inDirection;}
		void setButtons(int button, bool boolean){buttons[button] = boolean;}
		void resetTexture(){x1_tcoord = 0.0; y2_tcoord = 1.0;}
		void setPosition(float xx1, float xx2, float yy1, float yy2);
		// Draw Zero
		void draw();
		// Loads all textures
		void loadTextures();
		// When zero takes damage
		void depleteHealth(int block_number);
};