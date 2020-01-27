#pragma once
#include "Component.h"
#include "SDL.h"
#include "Entity.h"

enum ColliderLayer
{
	NoCollision = 0x01,
	EnemyCollidables = 0x02,	//Objects that collide with enemies
	PlayerCollidables = 0x04,	//Thing that collide with player objects
	NeutralCollidables = 0x08,	//Things that everything collides with
	PlayerProjectile = 0x10,	//Projectiles fired by the Player
	EnemyProjectile = 0x20,		//Projectiles fired by enemies
};
class CollisionComponent : public Component
{
public:
	CollisionComponent();
	CollisionComponent(unsigned char layer);
	CollisionComponent(unsigned char layer, Entity &parent);
	
	void Register();
	void Unregister();
	void HandleCollision(CollisionComponent *other);
	bool CheckCollision(CollisionComponent &other);
	SDL_Rect *m_BoundingBox;
	unsigned char m_Layer;
	void SetActive(bool active);
	bool GetActive();
private:
	bool m_Active = false;
};

