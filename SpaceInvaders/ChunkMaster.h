#pragma once
#include "CollisionComponent.h"
#include <vector>
#include <set>

#include "Graphics.h"

class ChunkMaster
{
public:
	ChunkMaster();

	void UpdateChunks();
	bool CheckChunkForCollision(int x, int y);
	bool CheckNeighboringChunks(int x, int y);
	void Register(CollisionComponent &component);
private:
	int screenWidthChunks;
	int screenHeightChunks;
	std::vector<CollisionComponent*> m_Chunks[8][8];
	std::set<CollisionComponent, CollisionComponent> m_ActiveCollisions;
	
};

