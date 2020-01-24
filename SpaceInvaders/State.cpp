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
				delete *iter; //I think this works the way i think it does. This should be all good in the hood.
			}
		}
		m_NextStateList->clear();
		delete m_NextStateList;
	}
	//I should not delete the parent. This should be deleted by its parent.
	m_pParentState = nullptr; 
	m_MasterStateMachine = nullptr;
}

void State::GoToNext(State *state, bool(*NextStateConditionFunc))
{
	//if our function pointer == nullptr then we should allow to proceed to the next state
	if (NextStateConditionFunc == nullptr || State::NextStateConditionFunc() && state != nullptr)
	{
		state->m_pParentState = this;

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
		while (parent != nullptr || !parent->m_IsRootNode)
		{
			if (parent == state)
			{
				return true;
			}
			parent = m_pParentState;
		}	
	}
	return false;
}

void State::OnEnter()
{
	m_CurrentPhase = OnEnterPhase;
	if (OnEnterState != nullptr)
	{
		OnEnterState();
	}
}

void State::OnLeave()
{
	m_CurrentPhase = OnLeavePhase;
	if (OnLeaveState != nullptr)
	{
		OnLeaveState();
	}
	m_CurrentPhase = InactivePhase;
}

void State::Update(float deltaTime)
{
	if (StateUpdateFunc != nullptr)
	{
		StateUpdateFunc(deltaTime);
	}
}

void State::TimedUpdate(float deltaTime)
{
}

State *State::AddChildState(State* state)
{
	SDL_assert(m_NextStateList != nullptr);
	if (state != nullptr)
	{
		m_NextStateList->push_back(state);
	}
	return state;
}