#pragma once
#include "CollisionComponent.h"
#include "Engine.h"
#include <list>

class CollisionComponent;

class CollisionManager
{
public:
	static void Init();
	static void CleanUp();
	static void RegisterComponent(CollisionComponent &component);
	static void RemoveComponent(CollisionComponent &component);
	static void CheckForCollisions();
private:
	CollisionManager();
	static void ClearInactives();
	static std::list<CollisionComponent*> *sProjectiles;
	static std::list<CollisionComponent*> *sCollidables;
};

