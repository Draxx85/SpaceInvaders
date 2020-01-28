#pragma once
#include "Entity.h"
#include "Player.h"
#include "EnemyGrid.h"
#include "ShipBlock.h"
#include "Boss.h"
#include "Graphics.h"
#include "Floater.h"
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void StartGame(int level);

	float m_RoundCountDown = 0.0f;
	int m_Lives = 3;
	bool m_GameActive = false;
	bool m_GameReadyToStart = false;
	bool m_FinishedCleaning = false;
	bool m_ShouldQuit = false;
	void InitializeRoundLoop(float deltaTime);
	void BetweenRoundCleanUp();
	void Update();

	void CreateRoundIntermission();
	void UpdateScore(int value);
	void AddFloater(SVector2D pos, int value);
private:
	void BuildArena();
	void AddPlayer();
	void CreateLevel();
	void BuildUI();
	Game *m_Game;
	const float kRoundTime = 2.f;

	std::vector<Floater*> *m_Floaters;

	int m_Score;
	
	int m_Multiplier;
	int m_levelIndex = 1;
	SDL_Color m_Color;

	Player *m_Player;
	EnemyGrid *m_EnemyGrid;
	ShipBlock *m_ShipBlocks[3];
	Boss *m_Boss;

	//UI Entities
	Floater *m_ScoreEntity;

	Floater *m_PlayerStatusEntity;

	Entity *m_SSLarian;
	Entity *m_Background;

};

