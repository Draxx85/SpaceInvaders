#pragma once
#include "Enemy.h"
#include "Level.h"

//class Level;
class EnemyGrid : public Entity
{
public:
	EnemyGrid();
	void PopulateEnemyGrid(int level);
	void ClearGrid();
	void UpdatePosition();
	void StartLevelBehaviour();
	void TimedUpdate(float deltaTime) override;
private:
	Enemy *m_pGrid[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth];
	std::vector<Enemy*> *m_EnemyPool;
	Level *m_pLevel;
	bool m_Movingleft = false;
	void CheckNextMoveDirection(Enemy *enemy);
};

