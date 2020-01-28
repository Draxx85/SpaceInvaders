#pragma once

class Process
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void TimedUpdate(float deltaTime) = 0;
	virtual void OnSafeClear() = 0;
};