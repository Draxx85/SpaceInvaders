#pragma once
#include <SDL.h>
#include "Entity.h"

class ShipBlockPiece : public Entity
{
public:
	virtual void DoCollision(unsigned char collisionType) override;
	~ShipBlockPiece();
};

class ShipBlock : public Entity
{
public:
	ShipBlock(SVector2D pos);
	~ShipBlock();
	void SetPosition(SVector2D pos);
	void SetScale(SVector2D pos);
	void ResetBlocks();
private:
	static const int skBlockWidth = 8;
	static const int skBlockHeight = 8;
	SDL_Texture *m_pTexture;
	ShipBlockPiece *m_Blocks[skBlockHeight][skBlockWidth];
};

