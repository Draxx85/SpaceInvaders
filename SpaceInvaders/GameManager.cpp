#include "GameManager.h"

StateMachine *GameManager::m_MainStateMachine = nullptr;
StateMachine *GameManager::m_GameStateMachine = nullptr;
MainMenu *GameManager::sMainMenu = nullptr;

void GameManager::Init()
{
	m_MainStateMachine = BuildMainStateMachine();
	sMainMenu = new MainMenu();
}

void GameManager::StartGame()
{

}

void GameManager::CleanGame()
{
	if (sMainMenu != nullptr)
	{
		delete sMainMenu;
	}
}

//This is a horrible long State Machine builder. This should be done via data...
//Init, Intro, Menu, Game, Exit
StateMachine *GameManager::BuildMainStateMachine()
{
	StateMachine *stateMachine = new StateMachine();
	
	//Build the state machine nodes
	State* state = stateMachine->CreateState((int)GState_Init, GameState_Init);
	state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Intro));
	state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Menu));
	state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Game));
	state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Exit));

	return stateMachine;
}

//GameState:Init
void GameState_Init(float Update)
{
	State *state = GameManager::m_MainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				SDL_Log("I am in the state Entry Phase");
				break;
			case OnStayPhase:
				SDL_Log("I am updateing myself");
			case OnLeavePhase:
				SDL_Log("Im ending this state");
		}
	}
}

//GameState:Intro
void GameState_Intro(float Update)
{
	State *state = GameManager::m_MainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				SDL_Log("I am in the state Entry Phase");
				break;
			case OnStayPhase:
				SDL_Log("I am updateing myself");
			case OnLeavePhase:
				SDL_Log("Im ending this state");
		}
	}
}

//GameState:Menu
void GameState_Menu(float Update)
{

}

////GameState:Game
void GameState_Game(float Update)
{

}

//GameState:Exit
void GameState_Exit(float Update)
{

}
