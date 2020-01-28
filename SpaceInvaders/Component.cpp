#include "Component.h"

Component::Component()
	:m_Parent(nullptr)
{

}

Component::Component(Entity &parent)
{
	m_Parent = &parent;
}

Component::~Component()
{

}

void Component::Update(float deltaTime)
{
}

void Component::TimedUpdate(float deltaTime)
{

}

void Component::OnSafeClear()
{
}

void Component::SetParent(Entity &parent)
{
	m_Parent = &parent;
}
