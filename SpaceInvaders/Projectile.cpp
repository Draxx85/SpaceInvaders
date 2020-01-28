#include "Projectile.h"


Projectile::Projectile()
	:m_Parent(nullptr), m_Sprite(nullptr)
{
	m_FiringDirection = 1;
}

Projectile::Projectile(int firingDirection, EProjectileColor &color, Actor *owner)
{
	m_FiringDirection = firingDirection;

	SpriteComponent *sprite =
		new SpriteComponent(*this, Graphics::LoadResource("Resources/SpaceInvaders-Sprite.png"));

	AddComponent(sprite);
	const int padding = 24;
	sprite->m_Sprite->SpriteSrcRect.h = 128;
	sprite->m_Sprite->SpriteSrcRect.w = 32;
	sprite->m_Sprite->SpriteSrcRect.x = (int)color * (128 + 24);
	sprite->m_Sprite->SpriteSrcRect.y = 0;
	sprite->m_Sprite->SpriteDestRect.h = 128;
	sprite->m_Sprite->SpriteDestRect.w = 32;
	SetScale(0.75f, 0.75f);
	m_Sprite = sprite;

	CollisionComponent *collider = new CollisionComponent(PlayerProjectile | EnemyCollidables, *this);
	AddComponent(collider);
	m_Parent = owner;
}

Projectile::~Projectile()
{
	m_Parent = nullptr;
}

void Projectile::Spawn(int xOffset, int yOffset)
{
	if (m_Parent != nullptr)
	{
		m_SpawnLocation = m_Parent->GetPosition();
		m_SpawnLocation.x += xOffset + 36; //Hack to deal with texture offset. More time and I would handle this properly
		m_SpawnLocation.y += yOffset;
	}
	if (m_Sprite != nullptr)
	{
		SetPosition(m_SpawnLocation);
		m_Sprite->SetVisible(true);
		CollisionComponent *coll;
		if (TryGetComponent<CollisionComponent>(*this, coll))
		{
			coll->Register();
		}
	}
	UpdateManager::RegisterTimedUpdate(this);
}

void Projectile::DeSpawn()
{
	UpdateManager::SafeClearTimedUpdate(this);
 		m_Sprite->SetVisible(false);
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Unregister();
	}
}

void Projectile::TimedUpdate(float DeltaTime)
{
	IncrementPosition(0, kProjectileSpeed*m_FiringDirection);
	SVector2D *pos = &GetPosition();
	if (pos->y < -Graphics::skSpriteSheetHeight || pos->y > Graphics::sWindowHeight+ Graphics::skSpriteSheetHeight)
	{
		DeSpawn();
	}
}

void Projectile::DoCollision(unsigned char layer)
{
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		if (coll->m_Layer & PlayerProjectile)
		{
			if (layer & (EnemyCollidables | NeutralCollidables | EnemyProjectile))
			{
				DeSpawn();
			}
			else SDL_Log("Something is funky here");
		}
		else if (coll->m_Layer & EnemyProjectile)
		{
			if (layer & (NeutralCollidables | PlayerCollidables | PlayerProjectile))
			{
				DeSpawn();
			}else SDL_Log("Something is funky here");
		}
		
	}
}

bool Projectile::IsActive()
{
	if (m_Sprite != nullptr)
	{
		return m_Sprite->IsVisible();
	}
	return false;
}
