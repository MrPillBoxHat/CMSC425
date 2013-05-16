#include <Windows.h>
#include <irrKlang.h>
#include "Sound.h"
#pragma comment(lib, "irrklang.lib")
using namespace irrklang;

Sound::Sound() : play(true)
{
	engine = irrklang::createIrrKlangDevice();
}

/**********************************************************************************************************
*  Game SFX
*	These functions play the game sound effects.  Things such as actions or mechanics will be played here
*
**********************************************************************************************************/
void Sound::stopSound()
{
	engine->stopAllSounds();
}

void Sound::playMusic(char *music)
{
	engine->stopAllSounds();
	if(play)
		engine->play2D(music, true);
}

void Sound::playCursorSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/cursor.wav", false);
}

void Sound::playSelectSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/menu_select.wav", false);
}

void Sound::playDestructionSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/destruction.wav", false);
}

void Sound::playBossDesturctionSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/Boss_Destruction.wav", false);
}

void Sound::playEntrySFX()
{
	if(play)
		engine->play2D("Sound Effects/game/entry.wav", false);
}

void Sound::playSaberSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/saber.wav", false);
}

void Sound::playXBusterSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/x_buster.wav", false);
}

void Sound::playZBusterSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/z_buster.wav", false);
}

void Sound::playDashSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/dash.wav", false);
}

void Sound::playJumpSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/jump.wav", false);
}

void Sound::playLandSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/land.wav", false);
}

void Sound::playDieSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/die.wav", false);
}

void Sound::playHealthSFX()
{
	engine->stopAllSounds();
	if(play)
		engine->play2D("Sound Effects/game/text.wav", false);
}

void Sound::playDamageSFX()
{
	if(play)
		engine->play2D("Sound Effects/X/damage2.wav", false);
}

/**********************************************************************************************************
*  X SFX
*	These functions play X's sound effects.  Things such as grunts and other vocals will be played here
*
**********************************************************************************************************/
void Sound::xPlayJumpSFX()
{
	if(play)
		engine->play2D("Sound Effects/X/jump.wav", false);
}

void Sound::xPlayHurtSFX()
{
	if(play)
	{
		engine->play2D("Sound Effects/X/damage.wav", false);
		playDamageSFX();
	}
}

void Sound::playChargeShotSFX()
{
	if(play)
		engine->play2D("Sound Effects/X/charge.wav", false);
}

/**********************************************************************************************************
*  Zero SFX
*	These functions play X's sound effects.  Things such as grunts and other vocals will be played here
*
**********************************************************************************************************/
void Sound::zeroPlayJumpSFX()
{
	if(play)
		engine->play2D("Sound Effects/game/jump.wav", false);
}

void Sound::zeroPlayHurtSFX()
{
	if(play)
		engine->play2D("Sound Effects/Zero/damage.wav", false);
}

void Sound::zeroPlaySaberSFX()
{
	if(play)
		engine->play2D("Sound Effects/Zero/saber.wav", false);
}