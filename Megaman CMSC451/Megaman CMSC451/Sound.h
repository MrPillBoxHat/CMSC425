/****************************************************************************************
* Music Class
*	This is the music player class.  It will play all music for the game depending on
*	state.
****************************************************************************************/
#include <irrKlang.h>
using namespace irrklang;
#pragma once

class Sound{
	private:
		ISoundEngine* engine;

	public:
		Sound();
		void playMusic(char *music);
		void playCursorSFX();
		void playSelectSFX();
		void playSaberSFX();
		void playXBusterSFX();
		void playZBusterSFX();
		void playDashSFX();
		void playJumpSFX();
		void playLandSFX();
		void playDamageSFX();
};