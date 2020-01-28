#include "GameManager.h"

StateMachine *GameManager::sMainStateMachine = nullptr;
StateMachine *GameManager::sGameStateMachine = nullptr;
MainMenu *GameManager::sMainMenu = nullptr;
Game *GameManager::sGame;
bool GameManager::sInGame = false;
int GameManager::m_LevelID = 0;

void GameManager::Init()
{
	sMainStateMachine = BuildMainStateMachine();
	sMainStateMachine->StartMachine();
}

void GameManager::CleanGameManager()
{
	SAFE_DELETE(sMainStateMachine);
	SAFE_DELETE(sGameStateMachine);
	SAFE_DELETE(sMainMenu);
	SAFE_DELETE(sGame)
}

void GameManager::StartGame()
{
	sInGame = true;
}

void GameManager::QuitGame()
{
	sInGame = false;
}

void GameManager::CleanGame()
{
	if (sMainMenu != nullptr)
	{
		SAFE_DELETE(sMainMenu);
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
	state->IsNextStateReady = []() { return ShallWePlayAGame(); };
	state = state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Game));
	state->IsNextStateReady = []() { return false; };
	state = state->AddChildState(stateMachine->CreateState((int)GState_Intro, GameState_Exit));
	state->IsNextStateReady = []() { return true; };

	return stateMachine;
}

StateMachine *GameManager::BuildGameStateMachine()
{
	return nullptr;
}

bool GameManager::ShallWePlayAGame()
{
	return sInGame;
}

//GameState:Init
void GameState_Init(float Update)
{
	State *state = GameManager::sMainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				//SDL_Log("GameState_Init:I am in the state Entry Phase");
				break;
			case OnStayPhase:
				//SDL_Log("GameState_Init: I am updateing myself");
				break;
			case OnExitPhase:
			//	SDL_Log("GameState_Init: Im ending this state");
				break;
		}
	}
}

//GameState:Intro
void GameState_Intro(float Update)
{
	State *state = GameManager::sMainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase: 
				break;
			case OnStayPhase:
				break;
			case OnExitPhase:
				break;
		}
	}
}

//GameState:Menu
void GameState_Menu(float Update)
{
	State *state = GameManager::sMainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				GameManager::sMainMenu = new MainMenu();
				break;
			case OnStayPhase:
				break;
			case OnExitPhase:
				SAFE_DELETE(GameManager::sMainMenu);
				break;
		}
	}
}

////GameState:Game
void GameState_Game(float Update)
{
	State *state = GameManager::sMainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				GameManager::BuildGameStateMachine();
				GameManager::sGame = new Game();
				GameManager::sGame->CreateRoundIntermission();
				break;
			case OnStayPhase:
				if (!GameManager::sGame->m_GameStarted)
				{
					GameManager::sGame->InitializeRoundLoop(Update); 
					
				}
				GameManager::sGame->Update();
				break;
			case OnExitPhase:

				break;
		}
	}
}

//GameState:Exit
void GameState_Exit(float Update)
{
	State *state = GameManager::sMainStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				SAFE_DELETE(GameManager::sGame);
				SDL_Event sdlevent;
				sdlevent.type = SDL_QUIT;
				SDL_PushEvent(&sdlevent);
				break;
			case OnStayPhase:
				break;
			case OnExitPhase:
				break;
		}
	}
}
