#pragma once

#include "Actor.h"
#include "Level.h"
#include <math.h> 

class Enemy : public Actor
{
public:
	Enemy(const EEnemyTypes *type);
	virtual void DoCollision(unsigned char collisionType) override;
	void PlayExplosion();
	virtual ~Enemy();
};