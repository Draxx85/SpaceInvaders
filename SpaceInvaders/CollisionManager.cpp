#include "CollisionManager.h"
#include "Projectile.h"

std::list<CollisionComponent*> *CollisionManager::sProjectiles;
std::list<CollisionComponent*> *CollisionManager::sCollidables;

void CollisionManager::Init()
{
	sProjectiles = new std::list<CollisionComponent*>();
	sCollidables = new std::list<CollisionComponent*>();
}

void CollisionManager::CleanUp()
{
	sProjectiles->clear();
	sCollidables->clear();

	SAFE_DELETE(sProjectiles);
	SAFE_DELETE(sCollidables);
}

void CollisionManager::RegisterComponent(CollisionComponent &component)
{
	if (component.m_Layer & (EnemyProjectile | PlayerProjectile))
	{
		sProjectiles->push_back(&component);
	}
	sCollidables->push_back(&component);
}

void CollisionManager::RemoveComponent(CollisionComponent &component)
{
	sProjectiles->remove(&component);
	sCollidables->remove(&component);
}

void CollisionManager::ClearInactives()
{
	sProjectiles->remove_if([](CollisionComponent *col)
	{
		return !col->GetActive();
	});

	sCollidables->remove_if([](CollisionComponent *col)
	{
		return !col->GetActive();
	});
}
void CollisionManager::CheckForCollisions()
{
	std::list<CollisionComponent*>::iterator iterA, iterB;
	for (iterA = sProjectiles->begin(); iterA != sProjectiles->end(); ++iterA)
	{
		Projectile *proj = static_cast<Projectile*>((*iterA)->m_Parent);
		if (proj->IsActive())
		{
			for (iterB = sCollidables->begin(); iterB != sCollidables->end(); ++iterB)
			{
				if (((*iterA)->m_Layer & PlayerProjectile) && ((*iterB))->m_Layer  & PlayerProjectile)
				{
					continue;
				}
 				if ((*iterA) != (*iterB) && (*iterA)->CheckCollision(*(*iterB)))
				{
					(*iterA)->HandleCollision((*iterB));
					(*iterB)->HandleCollision((*iterA));
				}
			}
		}

	}
	ClearInactives();

}
