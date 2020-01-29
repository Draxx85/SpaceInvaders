#include "Boss.h"
#include "GameManager.h"

const float Boss::skYStartingOffset = -20.f;
const float Boss::skXStartingOffset = -50.f;
const int Boss::skScoreValue = 300;
const int Boss::skBossSpriteSheetIndex = 10;

Boss::Boss()
{
	SpriteComponent *sprite =
		new SpriteComponent(*this, Graphics::LoadActorResource());
	
	AddComponent(sprite);
	CollisionComponent *collider = new CollisionComponent(EnemyCollidables, *this);
	AddComponent(collider);

	SetScale(0.5f, 0.5f);

	m_DieSound = new SoundComponent(AudioManager::LoadSFXResource("Resources/Explode.wav"));
	AddComponent(m_DieSound);

	m_ScoreValue = skScoreValue;
}

void Boss::Spawn()
{
	SpriteComponent *sprite;
	if (TryGetComponent<SpriteComponent>(*this, sprite))
	{
		sprite->m_Sprite->m_SpriteSheetIndex = skBossSpriteSheetIndex;
		sprite->SetSpriteMaxFrame(1);
		sprite->SetVisible(true);
		sprite->m_Sprite->SpriteSrcRect.h = sprite->m_Sprite->SpriteSrcRect.w = Graphics::skSpriteSheetWidth;
		sprite->m_Sprite->SpriteDestRect.h = sprite->m_Sprite->SpriteDestRect.w = Graphics::skSpriteSheetWidth;
		sprite->m_Sprite->SpriteSrcRect.x = Graphics::skSpriteSheetWidth * (sprite->m_Sprite->m_SpriteSheetIndex % Graphics::skSpritesPerRow);
		sprite->m_Sprite->SpriteSrcRect.y = (floor((float)sprite->m_Sprite->m_SpriteSheetIndex / (float)Graphics::skSpritesPerRow))*Graphics::skSpriteSheetHeight;
	}
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Register();
	}
}

void Boss::DoCollision(unsigned char collisionType)
{
	if (collisionType & PlayerProjectile)
	{
		GameManager::sGame->UpdateScore(m_ScoreValue);
		GameManager::sGame->AddFloater(GetPosition(), m_ScoreValue);
		PlayExplosion();
 		Die();
	}
}

void Boss::Activate()
{
	Spawn();
	SetPosition(skXStartingOffset, skYStartingOffset);
	UpdateManager::RegisterTimedUpdate(this);
}

void Boss::TimedUpdate(float deltaTime)
{
	IncrementPosition(3, 0);
	SVector2D pos = GetPosition();
	if (pos.x > Graphics::sWindowWidth + Graphics::skSpriteSheetWidth)
	{
		Despawn();
	}
	if (m_IsDying)
	{
		if (m_TimeTillDeath > 0)
		{
			m_TimeTillDeath -= deltaTime;
		}
		else
		{
			Despawn();
		}
	}
}

void Boss::Despawn()
{
	SpriteComponent *sprite;
	if (TryGetComponent<SpriteComponent>(*this, sprite))
	{
		sprite->SetVisible(false);
	}
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Unregister();
	}
	UpdateManager::SafeClearTimedUpdate(this);
}