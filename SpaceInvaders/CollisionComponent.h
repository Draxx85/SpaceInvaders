#pragma once
#include "Component.h"
#include "SDL.h"

class CollisionComponent : Component
{
public:
	CollisionComponent();

	SDL_Rect m_BoundingBox;
private:
	void RegisterSelfToChunkMaster();
};

