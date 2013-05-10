#pragma once
#include "constants.h"
#include <SOIL.h>
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

class X_Bullet
{
	private:
		// Position of bullet
		float x1,x2,y1,y2;
		float x1_tcoord, y2_tcoord;
		int damage;
		int state;
		int direction;
		int counter;

	public:
		// Constructor
		X_Bullet(float *position, int direction);
		// getters
		int getDamage(){return damage;}
		float getX2(){return x2;}
		float getX1(){return x1;}
		int getDirection(){return direction;}
		// setters
		void setX1Coord(float x){x1_tcoord = x;}
		void setDead(){state = DIE;}
		// public functions
		void collision();
		void draw(GLuint *texture);
};