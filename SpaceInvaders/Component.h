#pragma once
#include "Process.h"

class Entity;

class Component : public Process
{
public:
	Component();
	Component(Entity &parent);
	virtual ~Component();
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;
	virtual void OnSafeClear() override;
	virtual void SetParent(Entity &parent);

	Entity *m_Parent;
};
