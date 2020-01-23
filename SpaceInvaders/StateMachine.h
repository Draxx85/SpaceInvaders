#pragma once
#include "State.h"

class State;

class StateMachine
{
public:
	State* m_Root;
	State *m_ActiveState;
	int m_CurrentStateEnum = 0;

	StateMachine();
	~StateMachine();

	void StartMachine();
	
	State *CreateState(int stateId, void(*update)(float deltaTime));
	
};