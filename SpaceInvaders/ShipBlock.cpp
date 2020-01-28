#include "ShipBlock.h"
#include "Graphics.h"
#include "SpriteComponent.h"

ShipBlock::ShipBlock(SVector2D pos) 
{
	m_pTexture = Graphics::LoadResource("Resources/ShipBlock.png");
	int w, h;
	SDL_QueryTexture(m_pTexture, NULL, NULL, &w, &h);
	int bWidth = w / skBlockWidth;
	int bheight = h / skBlockHeight;
	for (int i = 0; i < skBlockWidth; ++i)
	{
		for (int j = 0; j < skBlockHeight; ++j)
		{
			m_Blocks[i][j] = new ShipBlockPiece();
			SpriteComponent *sprite = new SpriteComponent(*m_Blocks[i][j], m_pTexture);
			m_Blocks[i][j]->AddComponent(sprite);
			SDL_Rect rect;
			rect.x = i * bWidth;
			rect.y = j * bheight;
			rect.w = bWidth;
			rect.h = bheight;

			sprite->SetSrcRect(&rect);
			SDL_Rect dest;
			dest.w = bWidth;
			dest.h = bheight;
			sprite->m_Sprite->SpriteDestRect.w = bWidth;
			sprite->m_Sprite->SpriteDestRect.h = bheight;
			//sprite->SetDestRect(&rect);
			sprite->SetVisible(true);
			CollisionComponent *coll = new CollisionComponent(NeutralCollidables, *m_Blocks[i][j]);
			m_Blocks[i][j]->AddComponent(coll);
			coll->Register();
		}
	}
	SetScale(SVector2D(0.5, 0.5f));
	SetPosition(pos);
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
