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
	bool m_GameStarted = false;
	void InitializeRoundLoop(float deltaTime);
	void ActiveCleanUp();
	void Update();

	void CreateRoundIntermission();

private:
	void BuildArena();
	void AddPlayer();
	void CreateLevel();
	void BuildUI();

	const float kRoundTime = 2.f;

	std::vector<Floater*> *m_Floaters;

	int m_Score;
	int m_Multiplier;
	int m_levelIndex = 1;

	Player *m_Player;
	EnemyGrid *m_EnemyGrid;
	ShipBlock *m_ShipBlocks[3];
	Boss *m_Boss;

	//UI Entities
	Entity *m_ScoreEntity;
	Entity *m_StatusDisplayEntity;
	Entity *m_PlayerStatusEntity;

	Entity *m_SSLarian;
	Entity *m_Background;

};

