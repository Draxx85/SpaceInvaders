#pragma once
#include "Process.h"

class Component : Process
{
public:
	Component();

	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;
};