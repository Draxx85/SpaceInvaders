#pragma once
#include "Enemy.h"
#include "Level.h"

static const int skMaxEnemyGridWidth = 10;
static const int skMaxEnemyGridHeight = 8;

class EnemyGrid
{
public:
	EnemyGrid();
	void SpawnEnemyGrid(Level &level);
	void ClearGrid();
private:
	Enemy *m_Grid[skMaxEnemyGridWidth][skMaxEnemyGridHeight];
};

