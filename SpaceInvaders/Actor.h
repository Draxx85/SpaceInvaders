#pragma once
#include "Entity.h"
#include "Projectile.h"
#include "CollisionComponent.h"

enum ProjectileColor
{
	Blue = 3,
	Red = 4,
};

class Actor : public Entity
{
public:
	Actor();
	virtual ~Actor();
	void Move(const float x, const float y);
	virtual void Fire();
	void LoadProjectiles(ProjectileColor color);
	void Die();
protected:
	int m_MaxProjectiles = 1;
	std::vector<Projectile> m_ProjectilePool;
};

