#pragma once
#include "Component.h"
#include "SDL.h"

class CollisionComponent : Component
{
public:
	CollisionComponent();

	SDL_Rect m_BoundingBox;

	void HandleCollision(CollisionComponent &collider);

	bool CheckCollision(SDL_Rect &rect);
private:
	void RegisterSelfToChunkMaster();
};

