#pragma once
#include "constants.h"
#include <SOIL.h>
#include "Zero.h"
#include "BackGround.h"
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

class X_Bullet
{
	private:
		// Position of bullet
		float x1,x2,y1,y2;
		float hit_box[4];
		float x1_tcoord, y2_tcoord;
		int damage;
		int state;
		int direction;
		int counter;
		BackGround *bg;
		// Moves the bullet and detects whether it hits a wall
		void move();

	public:
		// Constructor
		X_Bullet(float *position, int direction, BackGround *inbg);
		X_Bullet(float *position, int direction, int filler, BackGround *inbg);
		// getters
		int getDamage(){return damage;}
		float getX2(){return x2;}
		float getX1(){return x1;}
		float *getHitBox(){return hit_box;}
		int getDirection(){return direction;}
		// setters
		void setX1Coord(float x){x1_tcoord = x;}
		void setDead(){state = DIE;}
		// public functions
		bool collision(Zero *zero);
		void draw(GLuint *texture);
		void drawCharge(GLuint *texture);
};