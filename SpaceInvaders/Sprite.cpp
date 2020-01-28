#include "Sprite.h"

Sprite::Sprite()
	:pBitmapTexture(nullptr)
{


}

Sprite::Sprite(int maxFrames)
	:pBitmapTexture(nullptr), m_MaxFrames(maxFrames)
{
	//not animated if there is only one frame;
}

Sprite::~Sprite()
{
	FreeTexture();
}

//Increments the frame of the sprite for animations
Sprite &Sprite::operator++()
{//Add sprite sheet index multiplied sprite width modulus sprites per sheet. Thats all i need to animate
	if (m_MaxFrames > 1)
	{
		m_CurrentFrame = (m_CurrentFrame < (m_MaxFrames - 1)) ? ++m_CurrentFrame : 0;
		NextFrame();
	}
	return *this;
}

Sprite &Sprite::operator++(int)
{
	if (m_MaxFrames > 1)
	{
		//There is no need for this to behave differently to the postfix increment operator
		m_CurrentFrame = (m_CurrentFrame < (m_MaxFrames-1)) ? ++m_CurrentFrame : 0;
		NextFrame();
	}
	return *this;
}

Sprite &Sprite::operator--()
{
	if (m_MaxFrames > 1)
	{
		m_CurrentFrame = (m_CurrentFrame > 0) ? --m_CurrentFrame : 0; //Don't want to support rewind wrap arounds
		PreviousFrame();
	}
	return *this;
}

Sprite &Sprite::operator--(int)
{
	if (m_MaxFrames > 1)
	{
		//There is no need for this to behave differently to the postfix decrement operator
		m_CurrentFrame = (m_CurrentFrame > 0) ? --m_CurrentFrame : 0; //Don't want to support rewind wrap arounds
		PreviousFrame();
	}
	return *this;
}

void Sprite::FreeTexture()
{
	if (pBitmapTexture != nullptr)
	{
	//	SDL_DestroyTexture(pBitmapTexture); this is pooled
		pBitmapTexture = nullptr;
	}
}

void Sprite::NextFrame()
{
	int index = (m_CurrentFrame) + m_SpriteSheetIndex;
	//HACK: 8 is the number of sprites per row
	SpriteSrcRect.x = (index % 8) * skSpriteWidth;
	SpriteSrcRect.y = (index / 8) * skSpriteHeight;
	/*
	if (m_CurrentFrame >= (m_MaxFrames-1) && m_MaxFrames > 1)
	{
		SpriteSrcRect.x = m_CurrentFrame * skSpriteWidth;
	}
	else if (m_CurrentFrame <= (m_MaxFrames-1) && m_MaxFrames > 1)
	{
		SpriteSrcRect.x += skSpriteWidth;
	}*/
}

void Sprite::PreviousFrame()
{
}

