#include "Enemy.h"

Enemy::Enemy(const EEnemyTypes *type)
{
	SpriteComponent *sprite =
		new SpriteComponent(*this, Graphics::LoadActorResource());
	int spritePos = *type;
	AddComponent(sprite);

	sprite->m_Sprite->SpriteSrcRect.h = sprite->m_Sprite->SpriteSrcRect.w = Graphics::skSpriteSheetWidth;
	sprite->m_Sprite->SpriteDestRect.h = sprite->m_Sprite->SpriteDestRect.w = Graphics::skSpriteSheetWidth;
	sprite->m_Sprite->SpriteSrcRect.x = Graphics::skSpriteSheetWidth * (spritePos % Graphics::skSpritesPerRow);
	sprite->m_Sprite->SpriteSrcRect.y = (floor((float)spritePos / (float)Graphics::skSpritesPerRow))*Graphics::skSpriteSheetHeight;

	sprite->SetVisible(true);
	SetScale(0.65f, 0.65f);
}

Enemy::~Enemy()
{
}
