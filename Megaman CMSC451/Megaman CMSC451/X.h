/******************************************************
* Header file for Megaman X
*	Contains all function definitions
*   and state of the character
*******************************************************/
#pragma once

#include <GL\glut.h>

class X {
	// Contains X's health and location
	private:
		float x1,x2,y1,y2; // location of X
		float position[4]; // location of cannon
		int health;
		int state;
		int direction; // X facing direction
		int counter; // FPS controller
		float x1_tcoord; // texture x1 coord
		float y2_tcoord; // texture y2 coord
		GLuint textures[18]; // stores texture
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

	// Contains public functions
	public:
		// Contructor
		X();
		// getters
		int getState(){return state;}
		int getDirection(){return direction;}
		float *getCannon(){return position;}
		// setters
		void setHealth(int number){health += number;}
		void setState(int inState){state = inState; buttons[inState] = true;}
		void setDirection(int inDirection){direction = inDirection;}
		void setXPosition(float inx1, float inx2){x1 += inx1; x2 += inx2;}
		void setButtons(int button, bool boolean){buttons[button] = boolean;}
		void resetTexture(){x1_tcoord = 0.0; y2_tcoord = 1.0;}
		void setFrameOn(){play_3frame = true; frame_count = 1;}
		// Draw X
		void draw();
		// Loads all textures
		void loadTextures();
};