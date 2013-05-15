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
		void stopSound();
		// game SFX
		void playMusic(char *music);
		void playEntrySFX();
		void playCursorSFX();
		void playSelectSFX();
		void playDestructionSFX();
		void playSaberSFX();
		void playXBusterSFX();
		void playZBusterSFX();
		void playDashSFX();
		void playJumpSFX();
		void playLandSFX();
		void playDamageSFX();
		void playDieSFX();
		void playHealthSFX();
		// X SFX
		void xPlayHurtSFX();
		void xPlayJumpSFX();
		// Zero SFX
		void zeroPlayHurtSFX();
		void zeroPlayJumpSFX();
		void zeroPlaySaberSFX();
};