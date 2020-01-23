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
		m_NextStateList->clear();
		delete m_NextStateList;
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"State: NextState vector is no longer referenced by pointer. This memory has already been released!");
	}
	if (m_pParentState != nullptr)
	{
		delete m_pParentState;
	}
}

void State::GoToNext(State *state)
{

}

void State::TryGoToParent()
{
}
