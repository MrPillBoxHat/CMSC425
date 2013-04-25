#pragma once
class Player
{
public:
	Player(void);
	~Player(void);
	void setPos(double x, double y);
	void draw(void);
	void moveY(double delta);
	void moveX(double delta);

	GLdouble X() { return x; }
	GLdouble Y() { return y; }
	void setAngle(GLdouble angle) {this->angle = angle; } // radians
	GLdouble getAngle() {return angle; }
	void setDirection(bool x, GLdouble delta);
private:
	GLdouble x, y, z, angle;
	// the direction the character is facing
	unsigned char dir;

	void drawArm(double x, double angle);
	void drawLeg(double x, double angle);
	GLdouble getAngleInDegrees();

	static const char U = 0x1,
					  D = 0x2,
					  L = 0x4,
					  R = 0x8;
};

