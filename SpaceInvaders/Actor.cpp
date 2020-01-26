#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Move(const float x, const float y)
{
	IncrementPosition(x, y);
}

void Actor::Fire()
{

}

void Actor::LoadProjectiles(ProjectileColor color)
{
	STransform *tr = this->GetTransform();
	SDL_assert(tr != nullptr);
	for (int i = 0; i < m_MaxProjectiles; ++i)
	{
		Projectile *p = new Projectile();
		SpriteComponent *sprite =
			new SpriteComponent(*this, Graphics::LoadResource("Resources/SpaceInvaders-Sprite.png"));

		AddComponent(sprite);
		CollisionComponent *collider = new CollisionComponent();
		sprite->m_Sprite->SpriteSrcRect.h = sprite->m_Sprite->SpriteSrcRect.w = 128;
		sprite->m_Sprite->SpriteSrcRect.x = (int)color* 128;
		sprite->m_Sprite->SpriteSrcRect.y = 0;
		sprite->m_Sprite->SpriteDestRect.h = sprite->m_Sprite->SpriteDestRect.w = 128;
		p->SetPosition(tr->Position);

	}
	
}

void Actor::Die()
{
}
