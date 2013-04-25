#pragma once
#include "Movement.h"
class ThirdPerson :
	public Movement
{
public:
	ThirdPerson(Player *);
	~ThirdPerson(void);

	void update();
	void setUpCamera();
	void processNormalKeys(unsigned char key, int x, int y);
	void releaseNormalKeys(unsigned char ley, int x, int y);
	void mouseMove(int x, int y);
	void mouseButton(int button, int state, int x, int y);

private:
	const GLdouble RAD;
	GLdouble angD, deltaMove;

	void angleCamera();
};

