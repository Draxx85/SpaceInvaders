#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
	:m_Sprite(new Sprite())
{
	
}

SpriteComponent::~SpriteComponent()
{
	delete m_Sprite;
}

void SpriteComponent::Update(float deltaTime)
{
	UpdateSprite(deltaTime);
}

void SpriteComponent::TimedUpdate(float deltaTime)
{

}

void SpriteComponent::UpdateSprite(float deltaTime)
{
	m_TimeSinceAnimUpdate += deltaTime;

	//We need to see if enough time has passed to update animation frame
	if (m_TimeSinceAnimUpdate >= (1 / m_kAnimFrameRate)) 
	{
		m_Sprite++;
	}
}
