#pragma once
#include "Entity.h"
#include "Projectile.h"
//#include "CollisionComponent.h"

enum EProjectileColor
{
	Blue = 2,
	Red = 3,
};
class Projectile;

class Actor : public Entity
{
public:
	Actor();
	virtual ~Actor();
	void Move(const float x, const float y);
	virtual void Fire();
	void LoadProjectiles(int direction, EProjectileColor color);
	virtual void Die();
protected:
	int m_MaxProjectiles = 1;
	std::vector<Projectile*> *m_ProjectilePool;
};

