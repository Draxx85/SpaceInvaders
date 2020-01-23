#pragma once
#include "State.h"

class StateMachine
{
public:
	StateMachine(State* state);
	~StateMachine();

	State* StateEntry;
};