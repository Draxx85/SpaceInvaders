#include "StateMachine.h"

StateMachine::StateMachine()
	: m_Root(nullptr), m_ActiveState(nullptr)
{
}

StateMachine::~StateMachine()
{
	if (m_Root != nullptr)
	{
		//Recursivly delete states
		delete m_Root;
	}
}

void StateMachine::StartMachine()
{
	m_ActiveState = m_Root;
}

State *StateMachine::CreateState(int stateId, void(*update)(float deltaTime))
{
	bool IsRoot = this->m_Root == nullptr;

	State *state = new State(this, IsRoot);
	state->m_StateId = stateId;
	if (IsRoot)
	{
		m_Root = state;
	}
	state->StateUpdateFunc = update;
	return state;
}
