#pragma once

#include "X.h"
//#include <SOIL.h>

class World
{
private:
	int width;
	int height;
	X *x;

public:
	World(unsigned int w, unsigned int h);
	World() {}
	~World(void);

	void setSize(int w, int h);
	void update(void);
	void draw(void);
	void processKeys(unsigned char key, int x, int y);
	void mouseButton(int button, int state, int x, int y);

};