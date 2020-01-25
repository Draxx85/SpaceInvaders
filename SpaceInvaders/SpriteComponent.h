#pragma once

#include "SDL.h"
#include "Graphics.h"
#include "Component.h"
#include "Sprite.h"
#include "Entity.h"

struct SVector2D;
class Component;
class Entity;

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	SpriteComponent(Entity &parent);
	SpriteComponent(Entity &parent, SDL_Texture *texture);
	SpriteComponent(SDL_Texture *texture);

	virtual ~SpriteComponent() override;
	void SyncParentToComponent();
	Sprite *m_Sprite;

	void SetVisible(bool visible);
	const bool IsVisible();
	
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;

	void SetParent(Entity &component) override;

	void SetSrcRect(SDL_Rect *rect);
	void SetDestRect(SDL_Rect *rect);

	void UpdateSpritePos(SVector2D pos);

private:
	float const m_kAnimFrameRate = 24.0f;
	float m_TimeSinceAnimUpdate = 0.0f;
	void UpdateSprite(float deltaTime);
	bool m_IsVisible = false;
};