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
{
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
		SDL_DestroyTexture(pBitmapTexture);
		pBitmapTexture = nullptr;
	}
}

void Sprite::NextFrame()
{
	if (m_CurrentFrame >= (m_MaxFrames-1) && m_MaxFrames > 1)
	{
		SpriteSrcRect.x -= (m_MaxFrames-1) * skSpriteWidth;
	}
	else if (m_CurrentFrame <= (m_MaxFrames-1) && m_MaxFrames > 1)
	{
		SpriteSrcRect.x += skSpriteWidth;
	}
}

void Sprite::PreviousFrame()
{
}

