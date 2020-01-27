#include "AudioManager.h"

Mix_Music *AudioManager::spMusic = nullptr;

void AudioManager::Init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
		return;
	}
}

void AudioManager::LoadMusicResource(std::string res)
{
	spMusic = Mix_LoadMUS(res.c_str());
	if (spMusic == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load beat music! SDL_mixer Error: %s", Mix_GetError());
	}
}

void AudioManager::LoadSFXResource(std::string res)
{
}

void AudioManager::PlayMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(spMusic, -1);
	}
}

void AudioManager::Clean()
{
	ClearMusic();
	Mix_Quit();
}

void AudioManager::ClearMusic()
{
	Mix_FreeMusic(spMusic);
	spMusic = nullptr;
}
