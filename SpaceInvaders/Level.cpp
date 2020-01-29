#include "Level.h"
#include "Engine.h"
#include "LevelLoader.h"
Level::Level()
	: m_EnemyArray(new EEnemyTypes())
{
}

Level::~Level()
{
	SAFE_DELETE(m_EnemyArray);
}

const EEnemyTypes *Level::BuildLevel(int layout)
{
	switch (layout)
	{
		case 1:
			m_EnemyArray = &Level1[0][0];
			break;
		case 2:
			m_EnemyArray = &Level2[0][0];
			break;
		case 3:
			m_EnemyArray = &Level3[0][0];
			break;
		case 4:
			m_EnemyArray = &Level4[0][0];
			break;
		case 5:
			m_EnemyArray = &Level5[0][0];
		default:
			m_EnemyArray = &Level6[0][0];
			break;
		}
	return m_EnemyArray;
}

