#include "Entity.h"

Entity::Entity()
	:m_Transform(), m_Components(new std::vector<Component*>())
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

template<class T>
T& Entity::TryGetComponent(Entity &entity)
{
	for (int i = 0; i < entity.m_Components->size; ++i)
	{
		if (dynamic_cast<T*>(entity.m_Components[i]))
		{
			return &m_Components[i];
		}
	}
	return NULL;
}