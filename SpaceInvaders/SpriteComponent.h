#pragma once

#include "SDL.h"
#include "Component.h"
#include "Sprite.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	~SpriteComponent() override;
	Sprite *m_Sprite;
	
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;

private:
	float const m_kAnimFrameRate = 24.0f;
	float m_TimeSinceAnimUpdate = 0.0f;
	void UpdateSprite(float deltaTime);
};