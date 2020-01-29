#include "GameManager.h"

StateMachine *GameManager::sMainStateMachine = nullptr;
StateMachine *GameManager::sGameStateMachine = nullptr;
MainMenu *GameManager::sMainMenu = nullptr;
ButtonContainer *GameManager::m_Buttons = nullptr;
Game *GameManager::sGame;
Button *GameManager::m_RestartGame;
Button *GameManager::m_Exit;
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

void GameManager::Pause()
{
	UpdateManager::Pause(!UpdateManager::GetPausedState());
}

void GameManager::CleanGame()
{
	SAFE_DELETE(sMainMenu);
	SAFE_DELETE(sGame);
}

//This is a horrible long State Machine builder. This should be done via data...
//Init, Intro, Menu, Game, Exit
StateMachine *GameManager::BuildMainStateMachine()
{
	StateMachine *stateMachine = new StateMachine();
	
	//Build the state machine nodes
	State* state = stateMachine->CreateState((int)GState_Init, GameState_Init);
	state = state->AddChildState(stateMachine->CreateState((int)GState_Menu, GameState_Menu));
	state->IsNextStateReady = []() { return ShallWePlayAGame(); };
	state = state->AddChildState(stateMachine->CreateState((int)GState_Game, GameState_Game));
	state->IsNextStateReady = []() { return false; };
	state = state->AddChildState(stateMachine->CreateState((int)GState_Exit, GameState_Exit));
	state->IsNextStateReady = []() { return true; };

	return stateMachine;
}

//RoundStart, Gameplay, RoundEnd, Exit
StateMachine *GameManager::BuildGameStateMachine()
{
	StateMachine *stateMachine = new StateMachine();
	
	//Build the state machine nodes
	State* roundStart = stateMachine->CreateState((int)Game_RoundStart, InGame_RoundStart);
	roundStart->IsNextStateReady = []()
	{
		return GameManager::sGame->m_GameReadyToStart;
	};
	State *state = roundStart->AddChildState(stateMachine->CreateState((int)Game_Play, InGame_Play));
	state->IsNextStateReady = []() 
	{
		return !GameManager::sGame->m_GameActive;
	};
	state = state->AddChildState(stateMachine->CreateState((int)Game_RoundEnd, InGame_RoundEnd));
	state->IsNextStateReady = []()
	{
		return GameManager::sGame->m_FinishedCleaning;
	};
	state->AddChildState(roundStart);

	return stateMachine;
}

bool GameManager::ShallWePlayAGame()
{
	return sInGame;
}

//GameState:Init
void GameState_Init(float Update)
{
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
				GameManager::sGameStateMachine = GameManager::BuildGameStateMachine();
				GameManager::sGame = new Game();
				GameManager::sGameStateMachine->StartMachine();
				break;
			case OnStayPhase:
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

void InGame_RoundStart(float Update)
{
	State *state = GameManager::sGameStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				GameManager::sGame->CreateRoundIntermission();
				break;
			case OnStayPhase:
				GameManager::sGame->InitializeRoundLoop(Update);
				break;
			case OnExitPhase:
				break;
		}
	}
}

void InGame_Play(float Update)
{
	State *state = GameManager::sGameStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:

				break;
			case OnStayPhase:
				GameManager::sGame->Update(Update);
				break;
			case OnExitPhase:
				break;
		}
	}
}

void InGame_RoundEnd(float Update)
{
	State *state = GameManager::sGameStateMachine->m_ActiveState;
	if (state != nullptr)
	{
		switch (state->m_CurrentPhase)
		{
			case OnEnterPhase:
				GameManager::sGame->BetweenRoundCleanUp();
				break;
			case OnStayPhase:
				break;
			case OnExitPhase:
				break;
		}
	}
}