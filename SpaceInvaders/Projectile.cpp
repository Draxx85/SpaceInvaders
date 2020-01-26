#include "Projectile.h"


Projectile::Projectile()
	:m_Parent(nullptr), m_Sprite(nullptr)
{
	m_FiringDirection = 1;
}

Projectile::Projectile(int firingDirection, EProjectileColor color, Actor *parent)
{
	m_FiringDirection = firingDirection;

	SpriteComponent *sprite =
		new SpriteComponent(*this, Graphics::LoadResource("Resources/SpaceInvaders-Sprite.png"));

	AddComponent(sprite);
	CollisionComponent *collider = new CollisionComponent();
	sprite->m_Sprite->SpriteSrcRect.h = sprite->m_Sprite->SpriteSrcRect.w = 128;
	sprite->m_Sprite->SpriteSrcRect.x = (int)color * 128;
	sprite->m_Sprite->SpriteSrcRect.y = 0;
	sprite->m_Sprite->SpriteDestRect.h = sprite->m_Sprite->SpriteDestRect.w = 128;
	m_Sprite = sprite;
	m_Parent = parent;
}

Projectile::~Projectile()
{
	m_Parent = nullptr;
}

void Projectile::Spawn()
{
	UpdateManager::RegisterTimedUpdate(this);
	if (m_Parent != nullptr)
	{
		m_SpawnLocation = m_Parent->GetPosition();
	}
	if (m_Sprite != nullptr)
	{
		SetPosition(m_SpawnLocation);
		m_Sprite->SetVisible(true);
	}
}

void Projectile::TimedUpdate(float DeltaTime)
{
	IncrementPosition(0, m_ProjectileSpeed*m_FiringDirection);
}

bool Projectile::IsActive()
{
	if (m_Sprite != nullptr)
	{
		return m_Sprite->IsVisible();
	}
	return false;
}
