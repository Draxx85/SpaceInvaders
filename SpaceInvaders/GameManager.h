#pragma once
#include "SDL.h"
#include "Component.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "StateMachine.h"
#include "State.h"
#include "MainMenu.h"
#include "Game.h"

enum EGameState
{
	GState_Init = 0,
	GState_Intro = 1,
	GState_Menu = 2,
	GState_Game = 3,
	GState_Exit = 4,
};

enum EInGameState
{
	Game_RoundStart,
	Game_Play,
	Game_RoundEnd,
	Game_Exit,
};

class MainMenu;

class GameManager
{
public:
	static void Init();
	static void CleanGameManager();
	static void StartGame();
	static void CleanGame();
	static void QuitGame();
	static void Pause();
	static StateMachine *BuildMainStateMachine();
	static StateMachine *BuildGameStateMachine();

	static bool ShallWePlayAGame();

	static void RestartGame();

	static StateMachine *sMainStateMachine;
	static StateMachine *sGameStateMachine;

	static MainMenu *sMainMenu;
	static Game *sGame;

	static ButtonContainer *m_Buttons;
	static Button *m_RestartGame;
	
	static Button *m_Exit;
	static int m_LevelID;
private:
	GameManager();
	static bool sInGame;
};

void GameState_Init(float Update);
void GameState_Menu(float Update);
void GameState_Game(float Update);
void GameState_Exit(float Update);

void InGame_RoundStart(float Update);
void InGame_Play(float Update);
void InGame_RoundEnd(float Update);
