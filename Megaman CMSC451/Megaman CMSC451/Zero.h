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
		float cannon_position[4]; // location of cannon
		int current_health;
		int new_health;
		bool health_blocks[28];
		int state;
		int direction; // Zero facing direction
		int counter; // FPS controller
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
		void initHealth();

	// Contains public functions
	public:
		// Contructor
		Zero();
		// getters
		int getState(){return state;}
		int getDirection(){return direction;}
		float *getCannon(){return cannon_position;}
		float *getPosition();
		// setters
		void setState(int inState){state = inState; buttons[inState] = true;}
		void setHealth(int amount){new_health = current_health + amount;}
		void setDirection(int inDirection){direction = inDirection;}
		void setXPosition(float inx1, float inx2){x1 += inx1; x2 += inx2;}
		void setButtons(int button, bool boolean){buttons[button] = boolean;}
		void resetTexture(){x1_tcoord = 0.0; y2_tcoord = 1.0;}
		// Draw Zero
		void draw();
		// Loads all textures
		void loadTextures();
};