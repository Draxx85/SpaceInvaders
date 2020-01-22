#pragma once

#include "Process.h"

class Entity : Process
{
public:
	Entity();
	struct STransform *GetTransform();
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;

private:
	struct STransform *m_Transform;
};