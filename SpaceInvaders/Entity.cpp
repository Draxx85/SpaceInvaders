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
