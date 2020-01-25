#include "State.h"


State::State(StateMachine *owner, bool isRoot)
	: m_CurrentPhase(InactivePhase), m_MasterStateMachine(owner),
	m_IsRootNode(isRoot), m_NextStateList(new std::vector<State*>()),
	m_pParentState(nullptr)
{

}

State::~State()
{
	if (m_NextStateList != nullptr)
	{
		for (std::vector<State*>::iterator iter = m_NextStateList->begin(); iter != m_NextStateList->end(); ++iter)
		{
			//Make sure that we have a parent and double check we aren't going around in circles
			if (*iter != nullptr && !HasStateLooped(*iter))
			{
				delete *iter; //Recursive Delete
			}
		}
		m_NextStateList->clear();
		delete m_NextStateList;
	}
	//I should not delete the parent. This should be deleted by its parent.
	m_pParentState = nullptr;
	m_MasterStateMachine = nullptr;
}

void State::TryGoToNext(State *state)
{
	if (state != nullptr)
	{
		bool AllowEntryToNextState = false;
		if (IsNextStateReady == nullptr)
		{
			AllowEntryToNextState = true;
		}
		//if our function pointer == nullptr then we should allow to proceed to the next state
		else if (IsNextStateReady())
		{
			AllowEntryToNextState = true;
		}
		if (AllowEntryToNextState)
		{
			state->m_pParentState = this;
			m_CurrentPhase = OnExitPhase;
			m_NextState = state;
		}
	}
}

//Do I need this??
State* State::GetParent()
{
	return m_pParentState;
}


bool State::HasStateLooped(State* state)
{
	if (state != nullptr && !state->m_IsRootNode)
	{
		State* parent = m_pParentState;
		if (parent != nullptr)
		{
			while (!parent->m_IsRootNode)
			{
				if (parent == state)
				{
					return true;
				}
				parent = m_pParentState;
			}
		}
	}
	return false;
}

void State::DeactivateState()
{
	OnLeave();
}

void State::OnLeave()
{
	SDL_assert(m_NextState != nullptr);
	m_MasterStateMachine->m_ActiveState = m_NextState;
	m_NextState = nullptr;
}

void State::UpdateState(float deltaTime)
{
	if (StateUpdateFunc != nullptr)
	{
		StateUpdateFunc(deltaTime);
	}
	for (State* state : *m_NextStateList)
	{
		TryGoToNext(state);
	}
}

bool State::ReadyForNextState()
{
	return m_NextState != nullptr;
}

State *State::AddChildState(State* state)
{
	SDL_assert(m_NextStateList != nullptr);
	if (state != nullptr)
	{
		m_NextStateList->push_back(state);
		state->m_pParentState = this;
	}
	return state;
}