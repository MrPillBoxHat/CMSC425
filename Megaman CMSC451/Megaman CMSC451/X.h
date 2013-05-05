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
		GLuint textures[16]; // stores texture
		bool buttons[9]; // keeps track of state (buttons pressed)

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
		void move();
		void jump();
		void fire();
		void charge();
		void dash();
		// Responses
		void damage();
		void die();

	// Contains public functions
	public:
		/*********************************************************************************************
		* Enumerations
		*	Keeps track of the state of X and also creates symbols to make code easier to read 
		*	and program
		*
		*********************************************************************************************/
		static const enum directions {LEFT, RIGHT};
		static const enum states {STAND, MOVE, JUMP, FIRE, CHARGE, DASH, DAMAGE, DIE, ENTRY};
		static const enum texture_states{STAND_RIGHT, STAND_LEFT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT,
					FIRE_LEFT, FIRE_RIGHT, DASH_LEFT, DASH_RIGHT, DAMAGE_LEFT, DAMAGE_RIGHT,
					DIE_LEFT, DIE_RIGHT, CHARGE_TEXTURE, ENTRY_TEXUTRE};
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
		// Draw X
		void draw();
		// Loads all textures
		void loadTextures();
};