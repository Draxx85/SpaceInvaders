#include "SoundComponent.h"

SoundComponent::SoundComponent(Mix_Chunk *sound)
	:m_Sfx(sound)
{
	
}

SoundComponent::~SoundComponent()
{
	Mix_FreeChunk(m_Sfx);
	m_Sfx = nullptr;
}

void SoundComponent::Play()
{
	Mix_PlayChannel(-1, m_Sfx, 0);
}
