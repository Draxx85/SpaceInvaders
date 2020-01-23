#include "State.h"


State::State()
	: m_NextStateList(new std::vector<State*>()), 
	m_pParentState(nullptr), m_Phase(Inactive)
{

}

State::~State()
{
	if (m_NextStateList != nullptr)
	{
		for (std::vector<State*>::iterator iter = m_NextStateList->begin(); iter != m_NextStateList->end(); ++iter)
		{
			if (*iter != nullptr)
			{
				delete *iter; //I think this works the way i think it does. This should be all good in the hood.
			}
		}
		m_NextStateList->clear();
		delete m_NextStateList;
	}
	//I should not delete the parent. This should be deleted by its parent.
	m_pParentState = nullptr; 
}

void State::GoToNext(State *state, bool(*NextStateConditionFunc))
{
	if (NextStateConditionFunc == nullptr || State::NextStateConditionFunc())
	{

	}
}

void State::TryGoToParent()
{
}
