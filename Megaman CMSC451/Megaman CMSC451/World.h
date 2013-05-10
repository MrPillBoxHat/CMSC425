#pragma once

#include <list>
#include "X.h"
#include "Zero.h"
#include "BackGround.h"
#include "X_Bullet.h"
#include "Main_Menu.h"

class World
{
private:
	//dimensions of the world
	GLdouble width;
	GLdouble height;
	// Variables to keep track of frames per second
	int delta_time;
	int start_time;
	int current_time;
	int lapse_time;
	int frames;
	int fps;
	// Hero object
	X *x;
	Zero *zero;
	Main_Menu *menu;
	// Variables to keep track of objects and textures
	// in the world class
	std::list<X_Bullet> x_bullets;
	//std::list<Z_Bullet> z_bullets;
	BackGround bg;
	GLuint textures[4];
	bool main_menu;

	// lower left coordinate of the camera
	GLdouble cmX;
	// controls
	static const unsigned char MOVE_LEFT = 'a', MOVE_RIGHT = 'd', MOVE_JUMP = 'w', MOVE_DASH = 'j', MOVE_FIRE = 'h';

	void bullet_draw();
	void draw_helper();
	void loadTextures();
	void loadXBullet();
	void loadZBullet();
	void updateView();
	void processKeysMenu(unsigned char key);
	void processKeysGame(unsigned char key);
	void enableTextures();

public:
	World(GLdouble w, GLdouble h);
	World() {}
	~World(void);

	void setSize(int w, int h);
	void update(void);
	void draw(void);
	void processKeys(unsigned char key, int x, int y);
	void processKeyUp(unsigned char key, int x, int y);
};