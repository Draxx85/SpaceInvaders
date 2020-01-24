#pragma once
#include "State.h"

class State;

class StateMachine : Process
{
public:
	State* m_Root;
	State *m_ActiveState;
	int m_CurrentStateEnum = 0;

	StateMachine();
	~StateMachine();

	virtual void Update(float deltaTime);
	virtual void TimedUpdate(float deltaTime);

	void StartMachine();
	
	State *CreateState(int stateId, void(*update)(float deltaTime));
	
};