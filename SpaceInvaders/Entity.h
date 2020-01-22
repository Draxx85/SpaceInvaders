#pragma once

#include "Process.h"

struct SVector2D
{
	float x;
	float y;
};

struct STransform
{
	SVector2D Position;
	float angle;
	SVector2D Scale;
};

class Entity : Process
{
public:
	STransform GetTransform();
	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;

private:
	STransform m_Transform;
};