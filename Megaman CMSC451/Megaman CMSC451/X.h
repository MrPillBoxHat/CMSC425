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
		float x_coordinate;
		float y_coordinate;
		int health;
		int state;
		int direction;
		int counter;
		float x1_tcoord;
		float y2_tcoord;
		GLuint textures[16];

		// Private helper functions
		// Helper functions to load textures
		void loadEntry();
		void loadStand();
		void loadMove();
		void loadJump();
		void loadFire();
		void loadCharge();
		void loadDash();
		void loadDamage();
		void loadDie();

	// Contains public functions
	public:
		// Contructor
		X();
		// setters
		void setHealth(int number){health += number;}
		void setState(int inState){state = inState;}
		void setDirection(int inDirection){direction = inDirection;}
		// Draw X
		void draw();
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
		// Loads textures
		void loadTextures();
};