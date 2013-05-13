#include <Windows.h>
#include <irrKlang.h>
#include "Music.h"
using namespace irrklang;

Music::Music()
{
		engine = irrklang::createIrrKlangDevice();
}

void Music::play(char *music)
{
	engine->play2D(music, true);
}