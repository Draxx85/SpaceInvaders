#pragma once

#include "Actor.h"
#include "Level.h"
#include <math.h> 

class Enemy : public Actor
{
public:
	Enemy(const EEnemyTypes *type);
	virtual ~Enemy();
};