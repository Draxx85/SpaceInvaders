#pragma once
#include "SDL_mixer.h"
#include "SDL.h"
#include <string>

class AudioManager
{
public:
	
	static void Init();
	static void LoadMusicResource(std::string res);
	static void LoadSFXResource(std::string res);
	static void PlayMusic();
	static void Clean();
	static void ClearMusic();
private:
	AudioManager();
	static Mix_Music *spMusic;
};

