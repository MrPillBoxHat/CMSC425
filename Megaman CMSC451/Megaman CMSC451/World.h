#pragma once

#include "X.h"
#include "BackGround.h"

//#include <SOIL.h>

class World
{
private:
	int width;
	int height;
	// Variables to keep track of frames per second
	int delta_time;
	int start_time;
	int current_time;
	int lapse_time;
	int frames;
	int fps;
	// Hero object
	X *x;
	BackGround bg;	

	// lower left coordinate of the camera
	int cmX;
	// controlls
	static const unsigned char LEFT = 'a',
						       RIGHT = 'd';
	// how much left and right move
	static const int CM_DIFF = 4;

public:
	World(unsigned int w, unsigned int h);
	World() {}
	~World(void);

	void setSize(int w, int h);
	void update(void);
	void draw(void);
	void processKeys(unsigned char key, int x, int y);
	void mouseButton(int button, int state, int x, int y);
	void processKeyUp(unsigned char key, int x, int y);
};