#pragma once

#include <list>
#include "X.h"
#include "Zero.h"
#include "BackGround.h"
#include "X_Bullet.h"

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
	// Variables to keep track of objects and textures
	// in the world class
	std::list<X_Bullet > bullets;
	BackGround bg;
	GLuint bullet_texture;
	int game_state;

	// lower left coordinate of the camera
	GLdouble cmX;
	// controls
	static const unsigned char MOVE_LEFT = 'a', MOVE_RIGHT = 'd', MOVE_JUMP = 'w', MOVE_DASH = 'j', MOVE_FIRE = 'h';
	enum states {INTRO, NEWGAME, CONTINUE, OPTION, TRAINING, INGAME};

	// how much left and right move
	static const GLdouble CM_WALK, CM_DASH;

	void loadTextures();
	void loadXBullet();
	void loadIntro();
	void loadNewGame();
	void loadContinue();
	void loadOption();
	void loadTraining();
	void bullet_draw();
	void draw_helper();
	void draw_game();
	void draw_intro();
	void updateView();
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