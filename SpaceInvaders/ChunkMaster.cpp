#include "ChunkMaster.h"

ChunkMaster::ChunkMaster()
	: m_Chunks (new std::vector<std::vector<CollisionComponent*>>())
{
}

void ChunkMaster::UpdateChunks()
{
}

bool ChunkMaster::CheckChunkForCollision(int x, int y)
{
	return false;
}
