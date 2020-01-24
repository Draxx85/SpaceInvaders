#pragma once
#include <vector>
#include <set>
#include "Process.h"
#include "SDL.h"
#include "StateMachine.h"
#include "UpdateManager.h"

enum EStatePhase
{
	InactivePhase,
	OnEnterPhase,
	OnStayPhase,
	OnExitPhase,
};

class StateMachine;

class State
{
public:
	State(StateMachine *owner, bool isRoot = false);
	~State();
	
	//Member  Variables
	EStatePhase m_CurrentPhase;
	StateMachine *m_MasterStateMachine;
	bool m_IsRootNode;
	int m_StateId = 0;

	//need some stuff for prerequisits before moving states
	void TryGoToNext(State *state, bool(*NextStateConditionFunc)());

	State* GetParent();
	
	//function pointers
	bool(*NextStateConditionFunc)();
	void(*StateUpdateFunc)(float deltaTime);
	void(*OnEnterState)(float deltaTime);
	void(*OnExitState)(float deltaTime);

	
	void UpdateState(float deltaTime);
	bool ReadyForNextState();

	State *AddChildState(State *state);
	void DeactivateState();

private:
	bool HasStateLooped(State *state);
	void OnLeave();
	std::vector<State*> *m_NextStateList; //This needs updating
	//std::set<State*, bool(*)()> m_NextStateListSet -> this would make more sense to have this instead of a vector
	State *m_pParentState;
	State *m_NextState;
};