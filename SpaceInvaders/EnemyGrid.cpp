#include "EnemyGrid.h"

EnemyGrid::EnemyGrid()
	:m_pLevel(new Level()), m_EnemyPool(new std::vector<Enemy*>())
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
					if (m_EnemyPool->size() > 0)
					{
						m_pGrid[i][j] = (*m_EnemyPool)[0];
						m_EnemyPool->pop_back();
					}
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
			m_pGrid[i][j]->IncrementPosition(1*(m_Movingleft ? -1 : 1), 0);
			CheckNextMoveDirection(m_pGrid[i][j]);
			if (m_pGrid[i][j]->IsDead())
			{
				Enemy *e = m_pGrid[i][j];
				SpriteComponent *sprite;
				if (TryGetComponent(*e, sprite))
				{
					sprite->SetVisible(false);
				}
				m_EnemyPool->push_back(e);
				m_pGrid[i][j] = nullptr;
			}
		}
	}	
}

void EnemyGrid::CheckNextMoveDirection(Enemy *enemy)
{
	SVector2D pos = enemy->GetPosition();
	int width = enemy->GetTransform()->DestRect->w; //gross, make this safer later! TODO:
	if (pos.x < 0)
	{
		m_Movingleft = false;
	}
	else if (pos.x >(Graphics::sWindowWidth - width))
	{
		m_Movingleft = true;
	}
}
