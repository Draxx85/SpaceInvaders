#pragma once
#include "Component.h"
#include "SDL_mixer.h"
#include "AudioManager.h"

class SoundComponent :
	public Component
{
public:
	SoundComponent(Mix_Chunk *sound);
	~SoundComponent();
	void Play();
private:
	Mix_Chunk *m_Sfx;
};

