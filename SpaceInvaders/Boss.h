#pragma once
#include "Enemy.h"

class Boss : public  Enemy
{
public:
	Boss();
	void Spawn();
	void Activate();
	void DoCollision(unsigned char collisionType)override;
	void TimedUpdate(float deltaTime) override;
	void Despawn();
};

