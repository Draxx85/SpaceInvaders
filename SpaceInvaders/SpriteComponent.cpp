#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
	:m_Sprite(new SSprite())
{
	
}

SpriteComponent::~SpriteComponent()
{
	delete m_Sprite;
}

void SpriteComponent::Update(float deltaTime)
{
	m_TimeSinceAnimUpdate += deltaTime;
	//if (m_TimeSinceAnimUpdate >= ) We need to see if enough time has passed to update animation frame
}

void SpriteComponent::TimedUpdate(float deltaTime)
{

}

void SpriteComponent::UpdateSpriteSrc()
{

}
