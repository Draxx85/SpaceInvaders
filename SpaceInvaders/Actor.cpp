#include "Actor.h"

Actor::Actor()
	: m_ProjectilePool(new std::vector<Projectile*>())
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

void Actor::LoadProjectiles(int direction, EProjectileColor color)
{
	STransform *tr = this->GetTransform();
	SDL_assert(tr != nullptr);
	for (int i = 0; i < m_MaxProjectiles; ++i)
	{
		Projectile *p = new Projectile(direction, color, this);
		p->SetPosition(tr->Position);
		m_ProjectilePool->push_back(p);
	}
}

void Actor::Die()
{
}
