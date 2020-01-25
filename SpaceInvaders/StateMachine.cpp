#include "StateMachine.h"

StateMachine::StateMachine()
	: m_Root(nullptr), m_ActiveState(nullptr)
{
}

StateMachine::~StateMachine()
{
	//Recursivly delete states
	SAFE_DELETE(m_Root);
	m_ActiveState = nullptr;
}

void StateMachine::Update(float deltaTime)
{
	if (m_ActiveState != nullptr)
	{
		switch (m_ActiveState->m_CurrentPhase)
		{
			case InactivePhase:
				m_ActiveState->m_CurrentPhase = OnEnterPhase;
				break;
			case OnEnterPhase:
				m_ActiveState->OnEnterState(deltaTime);
				m_ActiveState->m_CurrentPhase = OnStayPhase;
				break;
			case OnStayPhase:
				m_ActiveState->UpdateState(deltaTime);
				if (m_ActiveState->ReadyForNextState())
				{
					m_ActiveState->m_CurrentPhase = OnExitPhase;
				}
				break;
			case OnExitPhase:
				m_ActiveState->OnExitState(deltaTime);
				m_ActiveState->DeactivateState();
				m_ActiveState->m_CurrentPhase = InactivePhase;
				break;
			default: //Let the stay state determine when its time to change
				break;
		}
	}
}

void StateMachine::TimedUpdate(float deltaTime)
{
}

void StateMachine::StartMachine()
{
	m_ActiveState = m_Root;
	UpdateManager::RegisterUpdate(this);
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
	state->OnEnterState = update;
	state->OnExitState = update;
	return state;
}
