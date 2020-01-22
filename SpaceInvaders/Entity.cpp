#include "Entity.h"

Entity::Entity()
	:m_Transform()
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