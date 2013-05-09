#pragma once
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
		int direction;

	public:
		// Constructor
		X_Bullet(float *position, int direction);
		// getters
		int getDamage(){return damage;}
		float getX2(){return x2;}
		float getX1(){return x1;}
		int getDirection(){return direction;}
		// public functions
		void detec_collision();
		void draw(GLuint texture);
		void move();
};