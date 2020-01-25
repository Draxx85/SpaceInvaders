#pragma once
#include "Entity.h"
#include "Player.h"
#include "EnemyGrid.h"
#include "ShipBlock.h"
#include "Boss.h"

class Game
{
public:
	Game();
	~Game();

	
private:
	int m_Score;

	Player *m_Player;
	EnemyGrid *m_EnemyGrid;
	ShipBlock *m_ShipBlocks[3];
	Boss *m_Boss;

	//UI Entities
	Entity *m_ScoreEntity;
	Entity *m_StatusDisplayEntity;
	Entity *m_PlayerStatusEntity;

};

