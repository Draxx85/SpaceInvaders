#include "ShipBlock.h"
#include "Graphics.h"
#include "SpriteComponent.h"

ShipBlock::ShipBlock(SVector2D pos) 
{
	m_pTexture = Graphics::LoadResource("Resources/ShipBlock.png");
	int w, h;
	SDL_QueryTexture(m_pTexture, NULL, NULL, &w, &h);
	int bwidth = w / skBlockWidth;
	int bheight = h / skBlockHeight;
	for (int i = 0; i < skBlockWidth; ++i)
	{
		for (int j = 0; j < skBlockHeight; ++j)
		{
			m_Blocks[i][j] = MakeBlockPiece(i, j, bwidth, bheight);
		}
	}
	SetScale(SVector2D(0.5, 0.5f));
	SetPosition(pos);
}

void ShipBlock::ResetBlocks()
{
	for (int i = 0; i < skBlockWidth; ++i)
	{
		for (int j = 0; j < skBlockHeight; ++j)
		{
			m_Blocks[i][j]->Reset();
		}
	}
}

ShipBlock::~ShipBlock()
{
	SDL_DestroyTexture(m_pTexture);
	for (int i = 0; i < skBlockWidth; ++i)
	{
		for (int j = 0; j < skBlockHeight; ++j)
		{
			SAFE_DELETE(m_Blocks[i][j])
		}
	}
}

ShipBlockPiece *ShipBlock::MakeBlockPiece(const int x, const int y, const int width, const int height)
{
	ShipBlockPiece *piece = new ShipBlockPiece();
	SpriteComponent *sprite = new SpriteComponent(*piece, m_pTexture);
	piece->AddComponent(sprite);
	
	SDL_Rect rect;
	rect.x = x * width;
	rect.y = y * height;
	rect.w = width;
	rect.h = height;
	sprite->SetSrcRect(&rect);

	sprite->m_Sprite->SpriteDestRect.w = width;
	sprite->m_Sprite->SpriteDestRect.h = height;
	sprite->SetVisible(true);
	CollisionComponent *coll = new CollisionComponent(NeutralCollidables, *piece);
	piece->AddComponent(coll);
	coll->Register();

	return piece;
}

void ShipBlock::SetPosition(SVector2D pos)
{
	for (int i = 0; i < skBlockWidth; ++i)
	{
		for (int j = 0; j < skBlockHeight; ++j)
		{
			STransform *trans = m_Blocks[i][j]->GetTransform();
			m_Blocks[i][j]->SetPosition(pos.x+(i*trans->DestRect->w), pos.y+(j*trans->DestRect->h));
			
		}
	}
}

void ShipBlock::SetScale(SVector2D scale)
{
	for (int i = 0; i < skBlockWidth; ++i)
	{
		for (int j = 0; j < skBlockHeight; ++j)
		{
			m_Blocks[i][j]->SetScale(scale.x,scale.y);
		}
	}
}

void ShipBlockPiece::DoCollision(unsigned char collisionType)
{
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Unregister();
	}
	SpriteComponent *sprite;
	if (TryGetComponent<SpriteComponent>(*this, sprite))
	{
		sprite->SetVisible(false);
	}
}

void ShipBlockPiece::Reset()
{
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Register();
	}
	SpriteComponent *sprite;
	if (TryGetComponent<SpriteComponent>(*this, sprite))
	{
		sprite->SetVisible(true);
	}
}

ShipBlockPiece::~ShipBlockPiece()
{
	CollisionComponent *coll;
	if (TryGetComponent<CollisionComponent>(*this, coll))
	{
		coll->Unregister();
	}
}
