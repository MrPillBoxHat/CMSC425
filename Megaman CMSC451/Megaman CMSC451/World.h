#pragma once

#include <list>
#include "X.h"
#include "BackGround.h"
#include "X_Bullet.h"

using namespace std;

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
	list<X_Bullet> bullets;
	BackGround bg;

	// lower left coordinate of the camera
	int cmX;
	// controls
	static const unsigned char MOVE_LEFT = 'a',
						       MOVE_RIGHT = 'd',
							   MOVE_JUMP = 'w',
							   MOVE_DASH = 'j',
							   MOVE_FIRE = 'h';

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
	void processKeyUp(unsigned char key, int x, int y);
};