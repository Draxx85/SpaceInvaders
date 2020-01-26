#include "Entity.h"

Entity::Entity()
	:m_Transform(new STransform(0,0,0,0)), m_Components(new std::vector<Component*>())
{

}

Entity::~Entity()
{
	for (Component *comp : *m_Components)
	{
		if (comp != nullptr)
		{
			SAFE_DELETE(comp);
		}
	}
	m_Components->clear();
	delete m_Components;
	m_Components = nullptr;
	//m_Transforms points to child owned objects so we should let child components handle cleanup
	m_Transform = nullptr;
}

struct STransform *Entity::GetTransform()
{
	return m_Transform;
}

void Entity::Update(float deltaTime)
{
	
}

void Entity::TimedUpdate(float deltaTime)
{

}

void Entity::AddComponent(Component *Component)
{
	if (m_Components != nullptr)
	{
		m_Components->push_back(Component);
		Component->SetParent(*this);
	}
}

void Entity::SetPosition(SVector2D pos)
{
	m_Transform->SetPosition(pos);
}

void Entity::SetPosition(float x, float y)
{
	SVector2D pos = SVector2D(x, y);
	m_Transform->SetPosition(pos);
}


SVector2D &Entity::GetPosition()
{
	return m_Transform->Position;
}

SVector2D &Entity::GetScale()
{
	return m_Transform->Scale;
}

void Entity::SetScale(float x, float y)
{
	SVector2D scale = SVector2D(x, y);
	m_Transform->SetScale(scale);
}

void Entity::IncrementPosition(SVector2D &pos)
{
	m_Transform->IncrementPos(pos.x, pos.y);
}

void Entity::IncrementPosition(float x, float y)
{
	m_Transform->IncrementPos(x, y);
}