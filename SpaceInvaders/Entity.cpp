#include "Entity.h"

Entity::Entity()
	:m_Transform(new STransform), m_Components(new std::vector<Component*>())
{

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
	}
}
