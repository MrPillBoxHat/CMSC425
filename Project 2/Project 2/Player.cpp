#include "stdafx.h"
#include "Player.h"

#define PI 3.141592

Player::Player(void)
{
	dir = D;
}
Player::~Player(void)
{
}


void Player::setPos(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Player::moveY(double delta) {
	this->y += delta;
}

void Player::moveX(double delta) 
{
	this->x += delta;
}

void Player::draw(void)
{
	glColor3f(0.54, 0.54, 0.54);
	glTranslatef(x, y, 1);
	glRotated(getAngleInDegrees(), 0, 0, 1);

		//draw head
	glPushMatrix();
		glTranslatef(0, 0, .95);
		glutSolidSphere(.5, 10, 10);

		// Draw Nose (the nose is an orange cone)
		glColor3f(1.0, 0.5, 0.5); // nose is orange
		glPushMatrix();
			glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
			glutSolidCone(0.25, 1, 10, 2); // draw cone
		glPopMatrix();
	glPopMatrix();

	//draw body
	glPushMatrix();
		glColor3f(0.5, 0.0, 0.0);
		glScaled(1, 1, 2);
		glutSolidSphere(.25, 10, 10);
	glPopMatrix();

	// draw right arm
	drawArm(.4, -55);
	// draw left arm
	drawArm(-.4, 55);

	//draw right leg
	drawLeg(.15, 0);
	//draw left leg
	drawLeg(-.15, 0);
}

void Player::drawArm(double x, double angle) 
{
	glPushMatrix();
	glColor3ub(0, 255, 0);
		glRotated(angle, 0, 1, 0);
		glScaled(1, 1, 3);
		glTranslated(x, 0, -.05);
		glutSolidSphere(.1, 10, 10);
	glPopMatrix();
}

void Player::drawLeg(double x, double angle) 
{
	glPushMatrix();
	glColor3ub(0, 255, 0);
		//glRotated(angle, 0, 1, 0);
		glScaled(1, 1, 3);
		glTranslated(x, 0, -.18);
		glutSolidSphere(.1, 10, 10);
	glPopMatrix();
}

double Player::getAngleInDegrees()
{
	return angle * 180/PI;
}
