#pragma once

#include "SDL.h"
#include "Component.h"

struct SSprite
{
	SDL_Rect SpriteSrcRect;
	SDL_Rect SpriteDestRect;
	SDL_Texture *pBitmapTexture;
	int zOrder = 0;
};

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	~SpriteComponent() override;
	SSprite *m_Sprite;
	
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;

private:
	float const m_AnimFrameRate = 24.0f;
	float m_TimeSinceAnimUpdate = 0.0f;
	void UpdateSprite(float deltaTime);
};