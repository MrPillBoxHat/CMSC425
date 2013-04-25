#pragma once
#include "Movement.h"

class TopDownView :
	public Movement
{
public:
	TopDownView(Player * p1);
	~TopDownView(void);

	void update();
	void setUpCamera();
	void processNormalKeys(unsigned char key, int x, int y);
	void releaseNormalKeys(unsigned char ley, int x, int y);
	void mouseMove(int x, int y);
	void mouseButton(int button, int state, int x, int y);

private:
	unsigned char dir;

	GLdouble getAngle(unsigned char dir);
	unsigned char getDir(bool, GLdouble);

	static const char U = 0x1,
					  D = 0x2,
					  L = 0x4,
					  R = 0x8;
};

