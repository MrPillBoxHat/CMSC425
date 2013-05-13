#pragma once
#include <SOIL.h>
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL
#include "X.h"
#include "constants.h"

class Z_Bullet
{
	private:
		// Position of bullet
		float x1,x2,y1,y2;
		float hit_box[4];
		float x1_tcoord, y2_tcoord;
		int damage;
		int direction;
		int counter;

	public:
		// Constructor
		Z_Bullet(float *position, int direction);
		// getters
		int getDamage(){return damage;}
		float getX2(){return x2;}
		float getX1(){return x1;}
		float *getHitBox(){return hit_box;}
		int getDirection(){return direction;}
		// setters
		void setX1Coord(float x){x1_tcoord = x;}
		// public functions
		bool collision(X *x);
		void draw(GLuint *texture);
};