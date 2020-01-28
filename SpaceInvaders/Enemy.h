#pragma once

#include "Actor.h"
#include "Level.h"
#include <math.h> 
#include "SoundComponent.h"
class Enemy : public Actor
{
public:
	Enemy(const EEnemyTypes *type);
	virtual void DoCollision(unsigned char collisionType) override;
	void TimedUpdate(float deltaTime) override;
	void PlayExplosion();
	void Die() override;
	virtual ~Enemy();
	bool IsDead();
	void Fire() override;
	void Reset(const EEnemyTypes type);
	int m_ScoreValue;
private:
	SoundComponent *m_ShootSound;
	SoundComponent *m_DieSound;
	const float kTimeRequiredToDie = 0.35f;
	bool m_IsDying = false;
	bool m_IsDead = false;
	float m_TimeTillDeath = 0.0f;
};