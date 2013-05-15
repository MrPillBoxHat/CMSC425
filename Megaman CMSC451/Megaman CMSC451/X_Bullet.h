#pragma once
#include "constants.h"
#include <SOIL.h>
#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL
#include "Zero.h"

class X_Bullet
{
	private:
		// Position of bullet
		float x1,x2,y1,y2;
		float hit_box[4];
		float x1_tcoord, y2_tcoord;
		GLuint textures[2];
		int damage;
		int state;
		int direction;
		int counter;

	public:
		// Constructor
		X_Bullet(float *position, int direction);
		X_Bullet(float *position, int direction, int filler);
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
		void draw(GLuint *textures);
};