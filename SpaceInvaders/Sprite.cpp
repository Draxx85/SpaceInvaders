#include "Sprite.h"

Sprite::Sprite()
	:pBitmapTexture(nullptr)
{
}

Sprite::Sprite(int maxFrames)
	:pBitmapTexture(nullptr), m_MaxFrames(maxFrames)
{
}

Sprite::~Sprite()
{
	FreeTexture();
}

//Increments the frame of the sprite for animations
Sprite &Sprite::operator++()
{
	if (m_MaxFrames > 1)
	{
		m_CurrentFrame = (m_CurrentFrame < (m_MaxFrames - 1)) ? ++m_CurrentFrame : 0;
		UpdateFrame();
	}
	return *this;
}

Sprite &Sprite::operator++(int)
{
	if (m_MaxFrames > 1)
	{
		//There is no need for this to behave differently to the postfix increment operator
		m_CurrentFrame = (m_CurrentFrame < (m_MaxFrames-1)) ? ++m_CurrentFrame : 0;
		UpdateFrame();
	}
	return *this;
}

Sprite &Sprite::operator--()
{
	if (m_MaxFrames > 1)
	{
		//Don't want to support rewind wrap arounds
		m_CurrentFrame = (m_CurrentFrame > 0) ? --m_CurrentFrame : 0;
		UpdateFrame();
	}
	return *this;
}

Sprite &Sprite::operator--(int)
{
	if (m_MaxFrames > 1)
	{
		//There is no need for this to behave differently to the postfix decrement operator
		//Also Don't want to support rewind wrap arounds
		m_CurrentFrame = (m_CurrentFrame > 0) ? --m_CurrentFrame : 0; 
		UpdateFrame();
	}
	return *this;
}

void Sprite::FreeTexture()
{
	if (pBitmapTexture != nullptr)
	{
		//This is pooled
		pBitmapTexture = nullptr;
	}
}

void Sprite::UpdateFrame()
{
	int index = (m_CurrentFrame) + m_SpriteSheetIndex;

	SpriteSrcRect.x = (index % skSpritesPerRow) * skSpriteWidth;
	SpriteSrcRect.y = (index / skSpritesPerRow) * skSpriteHeight;
}

