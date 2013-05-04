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
		int damage;

	public:
		// Constructor
		X_Bullet(float xx1, float xx2, float yy1, float yy2);
		// getters
		int getDamage(){return damage;}
		void detec_collision();
};