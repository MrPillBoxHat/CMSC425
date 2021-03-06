#pragma once

#include <list>
#include "X.h"
#include "Zero.h"
#include "BackGround.h"
#include "X_Bullet.h"
#include "Z_Bullet.h"
#include "Main_Menu.h"
#include "ZeroAI.h"
#include "Saber.h"
#include "Sound.h"

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
	// Misc objects
	Main_Menu *menu;
	ZeroAI *zAI;
	Sound *sound;
	// Variables to keep track of objects and textures
	// in the world class
	std::list<X_Bullet> x_bullets;
	std::list<Z_Bullet> z_bullets;
	Saber *missile;
	Saber *saber;
	X_Bullet *chargeShot;
	BackGround bg;
	GLuint textures[8];
	// if in main menu
	bool main_menu;
	// checks if a missile was created
	bool create;
	// check if zero was created
	bool initZero;

	// lower left coordinate of the camera
	GLdouble cmX;
	// controls
	static const unsigned char MOVE_LEFT = 'a', MOVE_RIGHT = 'd', MOVE_JUMP = 'w', MOVE_DASH = 'j', MOVE_FIRE = 'h';

	void bullet_draw();
	void draw_helper();
	void loadTextures();
	void loadXBullet();
	void loadXCharge();
	void loadZBullet();
	void loadZBulletMissile();
	void updateView();
	void processKeysMenu(unsigned char key);
	void processKeysGame(unsigned char key);
	void processAI();
	void enableTextures();
	void createMissiles();
	void damage(int damage, int health);
	void initBossRoom();
	void resetHitBox();
	void testTexture();

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