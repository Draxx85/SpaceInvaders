#pragma once
#include "Process.h"

class Component : public Process
{
public:
	Component();
	virtual ~Component();
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;
};
