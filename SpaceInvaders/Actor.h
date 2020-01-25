#pragma once
#include "Entity.h"
class Actor :
	public Entity
{
	Actor();
	virtual ~Actor();
	void Move(float value);
	void Shoot();

	void Die();
};

