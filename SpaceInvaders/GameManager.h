#pragma once
#include "SDL.h"
#include "Component.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "StateMachine.h"
#include "State.h"
#include "MainMenu.h"

enum EGameState
{
	GState_Init = 0,
	GState_Intro = 1,
	GState_Menu = 2,
	GState_Game = 3,
	GState_Exit = 4,
};

class GameManager
{
public:
	static void Init();
	static void StartGame();
	static void CleanGame();

	static StateMachine *BuildMainStateMachine();

	static StateMachine *m_MainStateMachine;
	static StateMachine *m_GameStateMachine;

	static MainMenu *sMainMenu;
private:
	GameManager();
};

void GameState_Init(float Update);
void GameState_Intro(float Update);
void GameState_Menu(float Update);
void GameState_Game(float Update);
void GameState_Exit(float Update);
