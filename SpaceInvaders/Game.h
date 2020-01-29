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

	void StartGame();

	float m_RoundCountDown = 0.0f;
	int m_Lives = 3;
	bool m_GameActive = false;
	bool m_GameReadyToStart = false;
	bool m_FinishedCleaning = false;
	bool m_ShouldQuit = false;
	void InitializeRoundLoop(float deltaTime);
	void BetweenRoundCleanUp();
	void Update(float update);

	void CreateRoundIntermission();
	void UpdateScore(int value);
	void AddFloater(SVector2D pos, int value);
	void GameOver();
private:
	void BuildArena();
	void AddPlayer();
	void CreateLevel();
	void BuildUI();
	void UpdateHealth();

	Game *m_Game;
	const float kRoundTime = 2.f;

	std::vector<Floater*> *m_Floaters;

	int m_Score;
	
	int m_Multiplier;
	int m_levelIndex = 1;
	float m_BossCountDown;

	SDL_Color m_Color;

	Player *m_Player;
	EnemyGrid *m_EnemyGrid;
	ShipBlock *m_ShipBlocks[3];
	Boss *m_Boss;
	bool m_SpawnedBossThisRound = false;

	//UI Entities
	Floater *m_ScoreEntity;
	Floater *m_PlayerStatusEntity;

	//The reason for this name was that there was originally a story and a cutscene specced out.
	//Unfortunately I ran out of time and this feature was cut :(
	Entity *m_SSLarian; 
	Entity *m_Background;

};

