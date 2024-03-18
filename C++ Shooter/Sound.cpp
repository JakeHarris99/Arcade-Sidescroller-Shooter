#include "stdafx.h"
#include "Sound.h"

void Sound::init()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << Mix_GetError();
	}
	Mix_Volume(-1, 5);
	Mix_VolumeMusic(5);
	Mix_Music * backgroundMusic = Mix_LoadMUS("cache/sound/background.wav");
	Mix_PlayMusic(backgroundMusic, -1);
}