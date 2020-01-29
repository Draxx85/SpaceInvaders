#include "EnemyGrid.h"
#include "Game.h"

EnemyGrid::EnemyGrid()
	:m_pLevel(new Level()), m_EnemyPool(new std::vector<Enemy*>())
{
	ClearGrid();
	m_Transform->DestRect = new SDL_Rect();
	SetPosition(0, kDownALevelValue);
}

EnemyGrid::~EnemyGrid()
{
	ClearGrid();
	for (size_t i = 0; i < m_EnemyPool->size(); ++i)
	{
		SAFE_DELETE((*m_EnemyPool)[i]);
	}
	m_EnemyPool->clear();
	SAFE_DELETE(m_EnemyPool);
}

//Populate the grid by getting a level file from  the level builder
void EnemyGrid::PopulateEnemyGrid(int level)
{
	m_Level = level;
	m_EnemyCount = 0;
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
					++m_EnemyCount;
				}
			}
		}
	}
	UpdatePosition();
}

void EnemyGrid::ClearGrid()
{	
	m_RoundScore = 0;
	UpdateManager::ClearTimedUpdate(this);
	for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
	{
		for (int j = 0; j < Level::skMaxEnemyGridWidth; j++)
		{
			if (m_pGrid[i][j] != nullptr)
			{
				m_EnemyPool->push_back(m_pGrid[i][j]);
			}
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

void EnemyGrid::EnableGrid()
{
	for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
	{
		for (int j = 0; j < Level::skMaxEnemyGridWidth; j++)
		{
			if (m_pGrid[i][j] != nullptr)
			{
				m_pGrid[i][j]->Enable();
			}
		}
	}
	EnemyGrid::StartLevelBehaviour();
}

void EnemyGrid::TimedUpdate(float deltaTime)
{	
	SVector2D vec = GetPosition();
	int y = m_DirectionChanged ? kDownALevelValue : 0;
	m_DirectionChanged = false;
	bool didDirChange = m_Movingleft;
	int speedMod = m_EnemyCount == 1 ? 5 : 0;

	for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
	{
		for (int j = 0; j < Level::skMaxEnemyGridWidth; j++)
		{
			if (m_pGrid[i][j] == nullptr)
			{
				continue;
			}
			m_pGrid[i][j]->IncrementPosition(
				(m_LevelMoveMultiplier * m_Level + speedMod) * (m_Movingleft ? -1 : 1), y);
			
			CheckNextMoveDirection(m_pGrid[i][j]);
			CheckIfPlayerHasLostTheMatch(m_pGrid[i][j]);

			if (m_pGrid[i][j]->IsDead()) //if the enemy is dead remove them from the list
			{
				Enemy *e = m_pGrid[i][j];
				SpriteComponent *sprite;
				if (TryGetComponent(*e, sprite))
				{
					sprite->SetVisible(false);
				}
				m_EnemyPool->push_back(e);
				m_pGrid[i][j] = nullptr;
				--m_EnemyCount;
			}
			else //If enemy is not did this frame, give them a chance to shoot
			{
				int chance = static_cast<int>(rand() % 10000);
				if (chance < (m_ChanceToShoot*m_Level))
				{
					m_pGrid[i][j]->Fire();
				}
			}
		}
	}	
	m_DirectionChanged = didDirChange != m_Movingleft;

}

void EnemyGrid::CheckIfPlayerHasLostTheMatch(Enemy *e)
{
	SVector2D pos = e->GetPosition();
	if (pos.y >= m_LoseHeight)
	{
		m_Game->GameOver();
	}
}

bool EnemyGrid::CheckNextMoveDirection(Enemy *enemy)
{
	bool hasSwitched = m_Movingleft;
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
	return hasSwitched != m_Movingleft;
}