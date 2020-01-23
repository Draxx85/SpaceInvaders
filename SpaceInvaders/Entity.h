#pragma once

#include "Process.h"
#include "Component.h"
#include <vector>
#include "SpriteComponent.h"

struct SVector2D
{
	float x = 0.0f;
	float y = 0.0f;
};

struct STransform
{
	SVector2D Position;
	SVector2D Scale;
	float angle = 0.0f;
};

class Entity : Process
{
public:
	Entity();
	STransform *GetTransform();

	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;
	
	std::vector<Component*> *m_Components;

	void AddComponent(Component *Component);

	template<typename T>
	static bool TryGetComponent(Entity &entity, T* obj);

private:
	STransform *m_Transform;
	
};

template<typename T>
bool Entity::TryGetComponent(Entity &entity, T* obj)
{
	T* pt = nullptr;
	for (std::vector<Component*>::iterator iter = entity.m_Components->begin();
		iter != entity.m_Components->end(); ++iter)
	{
		pt = dynamic_cast<T*>(*iter);
		if (pt != nullptr)
		{
			obj = pt;
			return true;
		}
	}
	return false;
}