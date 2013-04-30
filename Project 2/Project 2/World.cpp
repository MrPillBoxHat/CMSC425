#include "stdafx.h"
//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
//	File: World.cpp - World methods
//----------------------------------------------------------------------


#include "World.h" // World definitions
#include "TopDownView.h"
#include "ThirdPerson.h"
#include "FirstPerson.h"
//----------------------------------------------------------------------
// World::World - initialize the world
//
// Initializes the camera position, resets various flags, and generates
// a 6x6 grid of snowmen, which are stored in a list.
//----------------------------------------------------------------------
World::World()  // World constructor
{
	views.push( new TopDownView(& tommy) );
	views.push( new ThirdPerson(& tommy) );
	views.push( new FirstPerson(& tommy) );
	view = views.front(); views.pop();
}

void World::init()
{
	RGBpixmap myPixmap;
	if (!myPixmap.readBMPFile("skybox-clouds.bmp", true)) {
		cerr << "File text0.bmp cannot be read or illegal format" << endl;
		exit(1);
	}
	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		myPixmap.nCols,
		myPixmap.nRows,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		myPixmap.pixel);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, myPixmap.nCols, myPixmap.nRows, 
		GL_RGB, GL_UNSIGNED_BYTE, myPixmap.pixel);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

//----------------------------------------------------------------------
// World::setAspectRatio - set window's aspect ratio
//----------------------------------------------------------------------
void World::setAspectRatio(float ratio) 
{
	view->setAspectRatio(ratio);
}

void World::setWH(GLint w, GLint h)
{
	this->w = w;
	this->h = h;
	view->setWH(w, h);
}


//----------------------------------------------------------------------
// World::update - update the world after each idle event
//
// Moves the camera (when up/down arrow key held) forward or backward by
// the amount saved in deltaMove.
//----------------------------------------------------------------------
void World::update() // update (with each idle event)
{
	view->update();

	glutPostRedisplay(); // redisplay everything
}

//----------------------------------------------------------------------
// World::draw - draw everything
//
// Moves the camera (when up/down arrow key held) forward or backward by
// the amount saved in deltaMove.
//----------------------------------------------------------------------
void World::draw()
{
	view->setUpCamera();

	drawBackground();

	createLight();

	tommy.draw();
}

// draw the ground - 200x200 square colored green
void World::drawBackground() 	
{
	glColor3f(0.0, .5, 0.5);
	double w = 8.0;
	glBegin(GL_POLYGON);
		glVertex3f(-w, -w, 0.0);
		//glVertex3f(-(w+10), 0, 0.0);
		glVertex3f(-w,  w, 0.0);

		glVertex3f(0, w+5 , 0.0);

		glVertex3f( w,  w, 0.0);
		//glVertex3f((w+5), 0, 0.0);
		glVertex3f( w, -w, 0.0);

		glVertex3f(0, -(w+5), 0.0);
	glEnd();

	//sky

	glEnable(GL_TEXTURE_2D);

	glColor3ub(255, 255, 255);
	w = 100;
	const GLfloat h = -2.0;
	glBegin(GL_POLYGON);
		glNormal3d(0, 0, 1);
		glTexCoord2f(0, 0);
		glVertex3f(-w, -w, h);

		glTexCoord2f(0, 1);
		glVertex3f(-w,  w, h);
		
		glTexCoord2f(1, 1);
		glVertex3f( w,  w, h);
		
		glTexCoord2f(1, 0);
		glVertex3f( w, -w, h);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void World::createLight()
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);


	GLfloat ambientIntensity[4] = {0.4, 0.4, 0.2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntensity);

	// set up light 0 properties
	GLfloat lt0Intensity[4] = {1.0, 1.0, 1.0, 1.0}; // white
	GLfloat lt0Position[4] = {0.0, 0, 4.0, 1.0}; // location
	createLight(GL_LIGHT0, lt0Intensity, lt0Position);

	GLfloat lt1Intensity[4] = {1.0, 1.0, 1.0, 1.0}; // white
	GLfloat lt1Position[4] = {0.0, -10.0, 4.0, 1.0}; // location
	createLight(GL_LIGHT1, lt1Intensity, lt1Position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void World::createLight(unsigned int light, GLfloat ints[], GLfloat pos[]) {
	glLightfv(light, GL_DIFFUSE, ints);
	glLightfv(light, GL_SPECULAR, ints);

	glLightfv(light, GL_POSITION, pos);
	// attenuation params (a,b,c)
	glLightf (light, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf (light, GL_LINEAR_ATTENUATION, 0.0);
	glLightf (light, GL_QUADRATIC_ATTENUATION, 0.1);
}
//----------------------------------------------------------------------
// Process keyboard events
// 
// When one of the arrow keys is first depressed, we set deltaMove.
// With each subsequent idle event, we move the camera by this amount
// based on the direction it is currently pointing.
//----------------------------------------------------------------------
void World::processNormalKeys(unsigned char key, int xx, int yy)
{
	if(key == 'c')
		changeCamera();
	else
		view->processNormalKeys(key, xx, yy);
} 

void World::releaseNormalKeys(unsigned char key, int xx, int yy) 
{
	view->releaseNormalKeys(key, xx, yy);
}
void World::pressSpecialKey(int key, int xx, int yy)
{

} 

void World::releaseSpecialKey(int key, int xx, int yy) 
{
	/*
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.0; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0; break;
	}
	*/
} 

//----------------------------------------------------------------------
// Process mouse drag events
// 
// This is called when dragging motion occurs. The variable
// angle stores the camera angle at the instance when dragging
// started, and deltaAngle is a additional angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void World::mouseMove(int xx, int yy) 
{ 	
	view->mouseMove(xx, yy);
}

void World::mouseButton(int button, int state, int xx, int yy) 
{
	view->mouseButton(button, state, xx, yy);
}

void World::changeCamera() 
{
	Movement * m = view;
	view = views.front(); views.pop();
	views.push(m);

	view->setWH(w, h);
}