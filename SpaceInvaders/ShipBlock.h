#pragma once
#include "SpriteComponent.h"

class CollisionComponent;

class ShipBlock : public Entity
{
public:
	ShipBlock();

private:
	CollisionComponent m_CollisionSpaces[12][12];
	SpriteComponent m_SpriteSpaces[12][12];
};

