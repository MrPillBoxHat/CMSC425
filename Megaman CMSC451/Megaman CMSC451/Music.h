/****************************************************************************************
* Music Class
*	This is the music player class.  It will play all music for the game depending on
*	state.
****************************************************************************************/
#include <irrKlang.h>
using namespace irrklang;
#pragma once

class Music{
	private:
		ISoundEngine* engine;

	private:
		Music();
		void play(char *music);
};