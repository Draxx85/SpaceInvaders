#pragma once
#include "CollisionComponent.h"
#include "Actor.h"

class Actor;

enum EProjectileColor;
class SpriteComponent;

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(int firingDirection, EProjectileColor &color, Actor *owner);
	~Projectile();

	Actor *m_Parent;
	SpriteComponent *m_Sprite;

	void Spawn(int xOffset, int yOffset);
	void DeSpawn();

	void TimedUpdate(float DeltaTime) override;
	void DoCollision(unsigned char layer) override;

	bool IsActive();
private:
	int m_FiringDirection;
	SVector2D m_SpawnLocation;
	const float kProjectileSpeed = 30;
};

