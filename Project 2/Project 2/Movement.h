#pragma once

#include "Player.h"

class Movement
{
public:
	Movement(Player * p1) { tommy = p1;}
	~Movement(void);

	void setAspectRatio(float aspectRatio) {this->aspectRatio = aspectRatio; }
	void setWH(GLint w, GLint h) { this->w=w; this->h=h; }

	virtual void update() = 0;
	virtual void setUpCamera() = 0;
	virtual void processNormalKeys(unsigned char key, int x, int y) = 0;
	virtual void releaseNormalKeys(unsigned char key, int x, int y) = 0;
	virtual void mouseMove(int x, int y) = 0;
	virtual void mouseButton(int button, int state, int x, int y) = 0;

protected:
	Player * tommy;

	float aspectRatio; // aspect ratio of graphics window
	float x, y, z; // camera position
	float deltaMoveY; // amount of incremental movement (when dragging)
	float deltaMoveX;

	float lx, ly, lz; // camera direction
	float angle; // angle of rotation for the camera direction
	float deltaAngle; // additional angle change (when dragging)

	bool isDragging; // true when mouse is dragging
	int xDragStart; // records the x-coordinate when dragging starts

	GLint w, h;
	// attributes
	static const unsigned char UP    = 'w',
							   DOWN  = 's',
							   LEFT  = 'a',
							   RIGHT = 'd';
};

