#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::CollisionComponent(unsigned char layer)
{
	m_Layer = layer;
}

CollisionComponent::CollisionComponent(unsigned char layer, Entity &parent)
{
	m_Layer = layer;
	SetParent(parent);
	if (m_Parent != nullptr)
	{
		STransform *trans = m_Parent->GetTransform();
		m_BoundingBox = trans->DestRect;
	}
}

void CollisionComponent::Register()
{
	CollisionManager::RegisterComponent(*this);
	m_Active = true;
}

void CollisionComponent::Unregister()
{
	m_Active = false;
}

void CollisionComponent::SetActive(bool active)
{
	m_Active = active;
}

bool CollisionComponent::GetActive()
{
	return m_Active;
}

void CollisionComponent::HandleCollision(CollisionComponent *other)
{
	if (m_Parent != nullptr)
	{
		m_Parent->DoCollision(other->m_Layer);
	}
}

bool CollisionComponent::CheckCollision(CollisionComponent &other)
{
	return SDL_HasIntersection(m_BoundingBox, other.m_BoundingBox);
}
