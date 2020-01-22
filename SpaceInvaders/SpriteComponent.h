#pragma once

#include "SDL.h"
#include "Component.h"

struct SSprite
{
	SDL_Rect SpriteRect;
	SDL_Rect TextureSrcRect;
};

class SpriteComponent : Component
{
public:
	SpriteComponent();
	~SpriteComponent();
	SSprite *m_Sprite;
	
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;

private:
	float const m_AnimFrameRate = 24.0f;
	float m_TimeSinceAnimUpdate = 0.0f;
	void UpdateSpriteSrc();
};