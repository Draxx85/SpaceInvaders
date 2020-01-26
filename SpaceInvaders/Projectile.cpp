#include "Projectile.h"


Projectile::Projectile()
	:m_Parent(nullptr), m_Sprite(nullptr)
{
	m_FiringDirection = 1;
}

Projectile::Projectile(int firingDirection, EProjectileColor &color, Actor *parent)
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

void Projectile::Spawn(int xOffset, int yOffset)
{
	if (m_Parent != nullptr)
	{
		m_SpawnLocation = m_Parent->GetPosition();
		m_SpawnLocation.x += xOffset;
		m_SpawnLocation.y += yOffset;
	}
	if (m_Sprite != nullptr)
	{
		SetPosition(m_SpawnLocation);
		m_Sprite->SetVisible(true);
	}
	UpdateManager::RegisterTimedUpdate(this);
}

void Projectile::DeSpawn()
{
	UpdateManager::SafeClearTimedUpdate(this);
	if (m_Sprite != nullptr)
	{
		m_Sprite->SetVisible(false);
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

bool Projectile::IsActive()
{
	if (m_Sprite != nullptr)
	{
		return m_Sprite->IsVisible();
	}
	return false;
}
