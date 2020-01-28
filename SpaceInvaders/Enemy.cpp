#include "Enemy.h"

Enemy::Enemy(const EEnemyTypes *type)
{
	SpriteComponent *sprite =
		new SpriteComponent(*this, Graphics::LoadActorResource());
	sprite->m_Sprite->m_SpriteSheetIndex = *type;
	AddComponent(sprite);
	CollisionComponent *collider = new CollisionComponent(EnemyCollidables, *this);
	AddComponent(collider);
	Reset(*type);
	m_ShootSound = new SoundComponent(AudioManager::LoadSFXResource("Resources/shoot.wav"));
	AddComponent(m_ShootSound);
	m_DieSound = new SoundComponent(AudioManager::LoadSFXResource("Resources/Explode.wav"));
	AddComponent(m_DieSound);
	UpdateManager::RegisterTimedUpdate(this);
}

void Enemy::DoCollision(unsigned char collisionType)
{
	if (collisionType & PlayerProjectile)
	{
		PlayExplosion();
		Die();
	}
}

void Enemy::TimedUpdate(float deltaTime)
{
	if (m_IsDying)
	{
		if (m_TimeTillDeath > 0)
		{
			m_TimeTillDeath -= deltaTime;
		}
		else
		{
			m_IsDead = true;
		}
	}
}

void Enemy::PlayExplosion()
{
	SpriteComponent *sprite;
	if (TryGetComponent<SpriteComponent>(*this, sprite))
	{
		sprite->SetSpriteMaxFrame(12);
		sprite->m_Sprite->m_SpriteSheetIndex = (int)Explosion;
		m_DieSound->Play();
	}
}

void Enemy::Die()
{
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Unregister();
	}
	m_TimeTillDeath = kTimeRequiredToDie;
	m_IsDying = true;
}

Enemy::~Enemy()
{
	UpdateManager::SafeClearTimedUpdate(this);
}

bool Enemy::IsDead()
{
	return m_IsDead;
}

void Enemy::Reset(const EEnemyTypes type)
{
	SpriteComponent *sprite;
	if (TryGetComponent<SpriteComponent>(*this, sprite))
	{
		sprite->m_Sprite->m_SpriteSheetIndex = type;

		sprite->m_Sprite->SpriteSrcRect.h = sprite->m_Sprite->SpriteSrcRect.w = Graphics::skSpriteSheetWidth;
		sprite->m_Sprite->SpriteDestRect.h = sprite->m_Sprite->SpriteDestRect.w = Graphics::skSpriteSheetWidth;
		sprite->m_Sprite->SpriteSrcRect.x = Graphics::skSpriteSheetWidth * (sprite->m_Sprite->m_SpriteSheetIndex % Graphics::skSpritesPerRow);
		sprite->m_Sprite->SpriteSrcRect.y = (floor((float)sprite->m_Sprite->m_SpriteSheetIndex / (float)Graphics::skSpritesPerRow))*Graphics::skSpriteSheetHeight;
		sprite->SetSpriteMaxFrame(2);
		SetScale(0.65f, 0.65f);
		sprite->SetVisible(true);
		UpdateManager::RegisterTimedUpdate(this);
	}
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Register();
	}
}


