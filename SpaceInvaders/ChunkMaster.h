#pragma once
#include "CollisionComponent.h"
#include <vector>

class ChunkMaster
{
public:
	ChunkMaster();


	void UpdateChunks();
	bool CheckChunkForCollision(int x, int y);
	bool CheckNeighboringChunks(int x, int y);
	std::vector<std::vector<CollisionComponent*>> *m_Chunks;
};

