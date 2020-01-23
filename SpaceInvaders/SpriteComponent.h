#pragma once

#include "SDL.h"
#include "Graphics.h"
#include "Component.h"
#include "Sprite.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	SpriteComponent(SDL_Texture *texture);
	~SpriteComponent() override;
	Sprite *m_Sprite;

	void SetVisible(bool visible);
	const bool IsVisible();
	
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;

	void SetSrcRect(SDL_Rect *rect);
	void SetDestRect(SDL_Rect *rect);

private:
	float const m_kAnimFrameRate = 24.0f;
	float m_TimeSinceAnimUpdate = 0.0f;
	void UpdateSprite(float deltaTime);
	bool m_IsVisible = false;
};