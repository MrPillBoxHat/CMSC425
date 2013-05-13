#include <Windows.h>
#include <irrKlang.h>
#include "Sound.h"
#pragma comment(lib, "irrklang.lib")
using namespace irrklang;

Sound::Sound()
{
	engine = irrklang::createIrrKlangDevice();
}

void Sound::playCursorSFX()
{
	engine->play2D("Sound Effects/menu_select.wav", false);
}

void Sound::playSelectSFX()
{
	engine->play2D("Sound Effects/menu_select.wav", false);
}

void Sound::playMusic(char *music)
{
	engine->stopAllSounds();
	engine->play2D(music, true);
}

void Sound::playEntrySFX()
{
	engine->play2D("Sound Effects/entry.wav", false);
}

void Sound::playSaberSFX()
{
	engine->play2D("Sound Effects/saber.wav", false);
}

void Sound::playXBusterSFX()
{
	engine->play2D("Sound Effects/x_buster.wav", false);
}

void Sound::playZBusterSFX()
{

}

void Sound::playDashSFX()
{
	engine->play2D("Sound Effects/dash.wav", false);
}

void Sound::playJumpSFX()
{
	engine->play2D("Sound Effects/jump.wav", false);
}

void Sound::playLandSFX()
{
	engine->play2D("Sound Effects/landing.wav", false);
}

void Sound::playDamageSFX()
{

}