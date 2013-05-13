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

}

void Sound::playSelectSFX()
{

}

void Sound::playMusic(char *music)
{
	engine->stopAllSounds();
	engine->play2D(music, true);
}

void Sound::playSaberSFX()
{

}

void Sound::playXBusterSFX()
{

}

void Sound::playZBusterSFX()
{

}

void Sound::playDashSFX()
{

}

void Sound::playJumpSFX()
{

}

void Sound::playLandSFX()
{

}

void playDamageSFX()
{

}