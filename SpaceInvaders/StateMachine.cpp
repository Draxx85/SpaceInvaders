#include "StateMachine.h"

StateMachine::StateMachine(State* state)
{
}

StateMachine::~StateMachine()
{
	if (StateEntry != nullptr)
	{
		//Recursivly delete states
		delete StateEntry;
	}
}
