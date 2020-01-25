#pragma once
#include "Entity.h"
class Actor : public Entity
{
public:
	Actor();
	virtual ~Actor();
	void Move(const float x, const float y);
	void Fire();

	void Die();
};

