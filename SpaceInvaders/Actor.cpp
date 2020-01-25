#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Move(const float x, const float y)
{
	float xPos = x, yPos = y;
	STransform *trans = GetTransform();
	if (trans != nullptr)
	{
		xPos = trans->Position.x + x;
		yPos = trans->Position.y + y;
	}
	SetPosition(SVector2D(xPos, yPos));
}

void Actor::Fire()
{
}

void Actor::Die()
{
}
