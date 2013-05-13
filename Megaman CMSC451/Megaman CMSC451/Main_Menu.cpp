#include <cstdlib>						// C++ standard definitions
#include <iostream>
#include "Main_Menu.h"
#include <GL/glut.h>                // GLUT
#include <SOIL.h>
#include "constants.h"
using namespace std;

Main_Menu::Main_Menu()
{
	menu_state = INTRO_PRESS;
	counter = 0;
}

void Main_Menu::draw()
{
	switch(menu_state)
	{
		// load intro game screen
		case INTRO:
			glBindTexture(GL_TEXTURE_2D, textures[INTRO]);
			// Switch screens to have "press Enter" appear
			counter++;
			if(counter % 60 == 0){
				menu_state = INTRO_PRESS;
				counter = 0;
			}
			break;

		// load intro game screen with press enter text
		case INTRO_PRESS:
			glBindTexture(GL_TEXTURE_2D, textures[INTRO_PRESS]);
			// Switch Screens to have "press Enter" disappear
			counter++;
			if(counter % 60 == 0){
				menu_state = INTRO;
				counter = 0;
			}
			break;
		
		// load selection screen with cursor on newgame
		case NEWGAME:
			glBindTexture(GL_TEXTURE_2D, textures[NEWGAME]);
			break;
			
		// load selection screen with cursor on continue
		case CONTINUE:
			glBindTexture(GL_TEXTURE_2D, textures[CONTINUE]);
			break;

		// load selection screen with cursor on option
		case OPTION:
			glBindTexture(GL_TEXTURE_2D, textures[OPTION]);
			break;

		// load selection screen with cursor on Training
		case TRAINING:
			glBindTexture(GL_TEXTURE_2D, textures[TRAINING]);
			break;
	}	
	// Draw a rectangle taking up the whole screen
	glBegin(GL_POLYGON);
		//real coord
		glTexCoord2d(0.0, 0.0);  glVertex2d(0.0, 0.0);
		glTexCoord2d(1.0, 0.0); glVertex2d(1000.0, 0.0);
		glTexCoord2d(1.0, 1.0); glVertex2d(1000.0, 650.0);
		glTexCoord2d(0.0, 1.0); glVertex2d(0.0, 650.0);
	glEnd();
}

void Main_Menu::loadTextures()
{
	loadIntro();
	loadNewGame();
	loadOption();
	loadContinue();
	loadTraining();
}

// Load main screen
void Main_Menu::loadIntro()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[INTRO] = SOIL_load_OGL_texture
	(
		"Main_Menu/Main_Menu_Blank.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[INTRO] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "MenutextureID: " << textures[INTRO] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[INTRO]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* loads entry image directly as a new OpenGL texture */
	textures[INTRO_PRESS] = SOIL_load_OGL_texture
	(
		"Main_Menu/Main_Menu.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[INTRO_PRESS] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "Main_MenutextureID: " << textures[INTRO_PRESS] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[INTRO_PRESS]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load main screen on NewGame select
void Main_Menu::loadNewGame()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[NEWGAME] = SOIL_load_OGL_texture
	(
		"Main_Menu/Main_Menu_Game_Start.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[NEWGAME] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "MenutextureID: " << textures[NEWGAME] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[NEWGAME]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load main screen on Continue select
void Main_Menu::loadContinue()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[CONTINUE] = SOIL_load_OGL_texture
	(
		"Main_Menu/Main_Menu_Continue.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[CONTINUE] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "MenutextureID: " << textures[CONTINUE] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[CONTINUE]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load main screen on Option select
void Main_Menu::loadOption()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[OPTION] = SOIL_load_OGL_texture
	(
		"Main_Menu/Main_Menu_Option.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[OPTION] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "MenutextureID: " << textures[OPTION] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[OPTION]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// Load main screen on Training select
void Main_Menu::loadTraining()
{
	/* loads entry image directly as a new OpenGL texture */
	textures[TRAINING] = SOIL_load_OGL_texture
	(
		"Main_Menu/Main_Menu_Training.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	/* check for an error during the load process */
	if( 0 == textures[TRAINING] )
	{
		cout << "SOIL loading error: " << SOIL_last_result() << endl;
		exit(0);
	}

	cout << "MenutextureID: " << textures[TRAINING] << endl;

	glBindTexture(GL_TEXTURE_2D, textures[TRAINING]); // select the active texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}