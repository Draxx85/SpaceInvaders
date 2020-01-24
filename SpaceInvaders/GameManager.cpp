#include "GameManager.h"

StateMachine *GameManager::m_MainStateMachine = nullptr;
StateMachine *GameManager::m_GameStateMachine = nullptr;
MainMenu *GameManager::sMainMenu = nullptr;

void GameManager::Init()
{
	m_MainStateMachine = BuildMainStateMachine();
	m_MainStateMachine->StartMachine();
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
	state = state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Intro));
	state = state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Menu));
	state->NextStateConditionFunc = []() { return false; };
	state = state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Game));
	state = state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Exit));

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
				SDL_Log("GameState_Init:I am in the state Entry Phase");
				break;
			case OnStayPhase:
				SDL_Log("GameState_Init: I am updateing myself");
				break;
			case OnExitPhase:
				SDL_Log("GameState_Init: Im ending this state");
				break;
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
				SDL_Log("GameState_IntroI am in the state Entry Phase");
				break;
			case OnStayPhase:
				SDL_Log("GameState_IntroI am updateing myself");
				break;
			case OnExitPhase:
				SDL_Log("GameState_IntroIm ending this state");
				break;
		}
	}
}

//GameState:Menu
void GameState_Menu(float Update)
{
	State *state = GameManager::m_MainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				GameManager::sMainMenu = new MainMenu();
				SDL_Log("GameState_MenuI am in the state Entry Phase");
				break;
			case OnStayPhase:
				SDL_Log("GameState_MenuI am updateing myself");
				break;
			case OnExitPhase:
				SDL_Log("GameState_MenuIm ending this state");
				break;
		}
	}
}

////GameState:Game
void GameState_Game(float Update)
{

}

//GameState:Exit
void GameState_Exit(float Update)
{

}
