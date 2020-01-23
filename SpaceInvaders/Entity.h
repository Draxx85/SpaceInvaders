#pragma once

#include "Process.h"
#include "Component.h"
#include <vector>

class Entity : Process
{
public:
	Entity();
	struct STransform *GetTransform();

	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;
	
	std::vector<Component*> *m_Components;
	void AddComponent(Component *Component);

	template<class T>
	static T& TryGetComponent(Entity &entity);
private:
	struct STransform *m_Transform;
	
};
