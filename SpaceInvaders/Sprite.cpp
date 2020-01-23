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
}

//Increments the frame of the sprite for animations
Sprite &Sprite::operator++()
{
	m_CurrentFrame = (m_CurrentFrame < m_MaxFrames) ? ++m_CurrentFrame : 0;
	NextFrame();
	return *this;
}

Sprite Sprite::operator++(int)
{
	//There is no need for this to behave differently to the postfix increment operator
	m_CurrentFrame = (m_CurrentFrame < m_MaxFrames) ? ++m_CurrentFrame : 0;
	NextFrame();
	return *this;
}

Sprite &Sprite::operator--()
{
	m_CurrentFrame = (m_CurrentFrame > 0) ? --m_CurrentFrame : 0; //Don't want to support rewind wrap arounds
	PreviousFrame();
	return *this;
}

Sprite Sprite::operator--(int)
{
	//There is no need for this to behave differently to the postfix decrement operator
	m_CurrentFrame = (m_CurrentFrame > 0) ? --m_CurrentFrame : 0; //Don't want to support rewind wrap arounds
	PreviousFrame();
	return *this;
}

void Sprite::NextFrame()
{
	
}

void Sprite::PreviousFrame()
{
}

