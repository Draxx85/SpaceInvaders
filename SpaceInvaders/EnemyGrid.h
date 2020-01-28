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
	void TimedUpdate(float deltaTime) override;
	Game *m_pGame;
	int m_EnemyCount = 0;
private:
	const int kDownALevelValue = 32;
	Enemy *m_pGrid[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth];
	std::vector<Enemy*> *m_EnemyPool;
	Level *m_pLevel;
	bool m_Movingleft = false;
	bool CheckNextMoveDirection(Enemy *enemy);
	bool m_DirectionChanged = false;
};

