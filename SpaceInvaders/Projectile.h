#pragma once
#include "Entity.h"
#include "CollisionComponent.h"
#include "Actor.h"

class Actor;
enum EProjectileColor;

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(int firingDirection, EProjectileColor color, Actor *parent);
	~Projectile();

	Actor *m_Parent;
	SpriteComponent *m_Sprite;

	void Spawn();
	void DeSpawn();

	void TimedUpdate(float DeltaTime) override;

	bool IsActive();
private:
	int m_FiringDirection;
	SVector2D m_SpawnLocation;
	const float m_ProjectileSpeed = 30;
};

