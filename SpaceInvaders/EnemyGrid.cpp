#include "EnemyGrid.h"

EnemyGrid::EnemyGrid()
	:m_pLevel(new Level())
{
	ClearGrid();
	m_Transform->DestRect = new SDL_Rect();
	SetPosition(0, 0);
	StartLevelBehaviour();
}

void EnemyGrid::PopulateEnemyGrid(int level)
{
	if (m_pLevel != nullptr)
	{
		const EEnemyTypes *layout = m_pLevel->BuildLevel(level);
		for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
		{
			for (int j = 0; j < Level::skMaxEnemyGridWidth; ++j)
			{
				if (*layout == BlankEnemyType)
				{
					m_pGrid[i][j] = nullptr;
					++layout;
				} 
				else
				{
					m_pGrid[i][j] = new Enemy(layout);
					++layout;
				}
			}
		}
	}
	UpdatePosition();
}

void EnemyGrid::ClearGrid()
{	
	for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
	{
		for (int j = 0; j < Level::skMaxEnemyGridWidth; j++)
		{
			m_pGrid[i][j] = nullptr;
		}
	}
}

void EnemyGrid::UpdatePosition()
{
	SVector2D vec = GetPosition();
	for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
	{
		for (int j = 0; j < Level::skMaxEnemyGridWidth; j++)
		{
			if (m_pGrid[i][j] == nullptr)
			{
				continue;
			}
			SVector2D scale = m_pGrid[i][j]->GetScale();
			m_pGrid[i][j]->SetPosition(vec.x+(j*(Graphics::skSpriteSheetWidth* scale.x)), vec.y+(i*(Graphics::skSpriteSheetWidth* scale.y)));
		}
	}
}

void EnemyGrid::StartLevelBehaviour()
{
	UpdateManager::RegisterTimedUpdate(this);
}

void EnemyGrid::TimedUpdate(float deltaTime)
{
	
	SVector2D vec = GetPosition();
	for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
	{
		for (int j = 0; j < Level::skMaxEnemyGridWidth; j++)
		{
			if (m_pGrid[i][j] == nullptr)
			{
				continue;
			}
			m_pGrid[i][j]->IncrementPosition(1, 0);
		}
	}	
}

bool EnemyGrid::ShouldNextMoveChangeDirection()
{
	return false;
}
