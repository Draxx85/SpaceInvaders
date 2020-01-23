#pragma once
#include <vector>
#include "Process.h"
#include "SDL.h"

enum StatePhase
{
	Inactive,
	OnEnter,
	OnStay,
	OnLeave,
};

class State : Process
{
public:
	State();
	~State();

	//need some stuff for prerequisits before moving states
	void GoToNext(State* state, bool(*NextStateConditionFunc));

	void TryGoToParent();
	bool(*NextStateConditionFunc)();

private:
	std::vector<State*> *m_NextStateList;
	State *m_pParentState;
	StatePhase m_Phase;
};