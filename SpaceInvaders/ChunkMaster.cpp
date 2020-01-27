#include "ChunkMaster.h"

//Check chunk for collisions
//Check neighbours
//Keep Track of checked objects
//clear tracked list

//Quick Dirty:
//Master of active Projectiles compare collision with active Enemies or allied objects depending on projectile type

ChunkMaster::ChunkMaster()
{
	int screenWidthChunks = Graphics::sWindowWidth / 8;
	int screenHeightChunks = Graphics::sWindowHeight / 8;
}

void ChunkMaster::UpdateChunks()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			CheckChunkForCollision(i, j);
			CheckNeighboringChunks(i, j);
		}
	}
}

bool ChunkMaster::CheckChunkForCollision(int x, int y)
{
	if (m_Chunks[x][y].size() > 0)
	{
		std::vector<CollisionComponent*>::iterator first, second;
		first = m_Chunks[x][y].begin();
		second = m_Chunks[x][y].begin() + 1;
		if (second == m_Chunks[x][y].end())
		{
			return false;
		}

		for (; second != m_Chunks[x][y].end(); ++second)
		{
			if ((*first)->CheckCollision(*(*second)))
			{
				(*first)->HandleCollision((*second));

			}
		}
	}
	return false;
}

bool ChunkMaster::CheckNeighboringChunks(int x, int y)
{
	return false;
}

void ChunkMaster::Register(CollisionComponent & component)
{
	m_Chunks[component.m_BoundingBox->y % 8][component.m_BoundingBox->x % 8].push_back(&component);
}
