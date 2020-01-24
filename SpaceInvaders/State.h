#pragma once
#include <vector>
#include "Process.h"
#include "SDL.h"
#include "StateMachine.h"

enum EStatePhase
{
	InactivePhase,
	OnEnterPhase,
	OnStayPhase,
	OnLeavePhase,
};

class StateMachine;

class State : Process
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
	void GoToNext(State *state, bool(*NextStateConditionFunc));

	State* GetParent();
	
	//function pointers
	bool(*NextStateConditionFunc)();
	void(*StateUpdateFunc)(float deltaTime);
	void(*OnEnterState)();
	void(*OnLeaveState)();

	//overrides
	virtual void Update(float deltaTime);
	virtual void TimedUpdate(float deltaTime);

	State *AddChildState(State *state);


private:
	bool HasStateLooped(State *state);
	void OnEnter();
	void OnLeave();
	std::vector<State*> *m_NextStateList;
	State *m_pParentState;
};