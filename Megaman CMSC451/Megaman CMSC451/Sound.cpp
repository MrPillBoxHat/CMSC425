#include <Windows.h>
#include <irrKlang.h>
#include "Sound.h"
#pragma comment(lib, "irrklang.lib")
using namespace irrklang;

Sound::Sound()
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
	engine->play2D(music, true);
}

void Sound::playCursorSFX()
{
	engine->play2D("Sound Effects/game/cursor.wav", false);
}

void Sound::playSelectSFX()
{
	engine->play2D("Sound Effects/game/menu_select.wav", false);
}

void Sound::playDestructionSFX()
{
	engine->play2D("Sound Effects/game/destruction.wav", false);
}

void Sound::playBossDesturctionSFX()
{
	engine->play2D("Sound Effects/game/Boss_Destruction.wav", false);
}

void Sound::playEntrySFX()
{
	engine->play2D("Sound Effects/game/entry.wav", false);
}

void Sound::playSaberSFX()
{
	engine->play2D("Sound Effects/game/saber.wav", false);
}

void Sound::playXBusterSFX()
{
	engine->play2D("Sound Effects/game/x_buster.wav", false);
}

void Sound::playZBusterSFX()
{
	engine->play2D("Sound Effects/game/z_buster.wav", false);
}

void Sound::playDashSFX()
{
	engine->play2D("Sound Effects/game/dash.wav", false);
}

void Sound::playJumpSFX()
{
	engine->play2D("Sound Effects/game/jump.wav", false);
}

void Sound::playLandSFX()
{
	engine->play2D("Sound Effects/game/land.wav", false);
}

void Sound::playDieSFX()
{
	engine->play2D("Sound Effects/game/die.wav", false);
}

void Sound::playHealthSFX()
{
	engine->stopAllSounds();
	engine->play2D("Sound Effects/game/text.wav", false);
}

void Sound::playDamageSFX()
{
	engine->play2D("Sound Effects/X/damage2.wav", false);
}

/**********************************************************************************************************
*  X SFX
*	These functions play X's sound effects.  Things such as grunts and other vocals will be played here
*
**********************************************************************************************************/
void Sound::xPlayJumpSFX()
{
	engine->play2D("Sound Effects/X/jump.wav", false);
}

void Sound::xPlayHurtSFX()
{
	engine->play2D("Sound Effects/X/damage.wav", false);
	playDamageSFX();
}

void Sound::playChargeShotSFX()
{
	engine->play2D("Sound Effects/X/charge.wav", false);
}

/**********************************************************************************************************
*  Zero SFX
*	These functions play X's sound effects.  Things such as grunts and other vocals will be played here
*
**********************************************************************************************************/
void Sound::zeroPlayJumpSFX()
{
	engine->play2D("Sound Effects/game/jump.wav", false);
}

void Sound::zeroPlayHurtSFX()
{
	engine->play2D("Sound Effects/Zero/damage.wav", false);
}

void Sound::zeroPlaySaberSFX()
{
	engine->play2D("Sound Effects/Zero/saber.wav", false);
}