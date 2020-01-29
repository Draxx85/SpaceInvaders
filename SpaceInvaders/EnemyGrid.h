#pragma once
#include "Enemy.h"
#include "Level.h"

class Game;
//class Level;
class EnemyGrid : public Entity
{
public:
	EnemyGrid();
	~EnemyGrid();
	void PopulateEnemyGrid(int level);
	void ClearGrid();
	void UpdatePosition();
	void StartLevelBehaviour();
	void EnableGrid();
	void TimedUpdate(float deltaTime) override;
	int m_EnemyCount = 0;
	int m_RoundScore = 0;
	Game *m_Game;
private:
	void CheckIfPlayerHasLostTheMatch(Enemy *e);
	
	int m_LoseHeight = 650;
	const int kDownALevelValue = 32;
	Enemy *m_pGrid[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth];
	std::vector<Enemy*> *m_EnemyPool;
	Level *m_pLevel;
	
	int m_Level;
	int m_ActiveMultiplier = 1;
	int m_LevelMoveMultiplier = 2;
	bool m_Movingleft = false;
	
	bool CheckNextMoveDirection(Enemy *enemy);
	bool m_DirectionChanged = false;
	int m_ChanceToShoot = 2;
};

