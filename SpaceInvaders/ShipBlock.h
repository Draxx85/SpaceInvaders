#pragma once
#include <SDL.h>
#include "Entity.h"

//This is an individual chunk of the Ship Block piece
class ShipBlockPiece : public Entity
{
public:
	virtual void DoCollision(unsigned char collisionType) override;
	void Reset();
	~ShipBlockPiece();
};

//This is the main part of the destructable shield on each level
class ShipBlock : public Entity
{
public:
	ShipBlock(SVector2D pos);
	~ShipBlock();
	ShipBlockPiece * MakeBlockPiece(const int x, const int y, const int width, const int height);
	void SetPosition(SVector2D pos);
	void SetScale(SVector2D pos);
	void ResetBlocks();
private:
	static const int skBlockWidth = 8;
	static const int skBlockHeight = 8;
	SDL_Texture *m_pTexture;
	ShipBlockPiece *m_Blocks[skBlockHeight][skBlockWidth];
};

