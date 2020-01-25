#pragma once

class Command
{
public:
	virtual void Execute(void*) = 0;
};