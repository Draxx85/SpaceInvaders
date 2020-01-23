#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
	:m_Sprite(new Sprite())
{
	
}

SpriteComponent::SpriteComponent(SDL_Texture *texture)
	: m_Sprite(new Sprite())
{
	m_Sprite->pBitmapTexture = texture;
	Graphics::SetSrcRectFromTexture(m_Sprite->pBitmapTexture, m_Sprite->SpriteSrcRect);
}

SpriteComponent::~SpriteComponent()
{
	delete m_Sprite;
}

void SpriteComponent::SetVisible(const bool visible)
{
	if (m_IsVisible != visible)
	{
		m_IsVisible = visible;
		if (visible)
		{
			Graphics::RegisterSpriteToDraw(this);
		}
		else
		{
			Graphics::RemoveSpriteFromDrawList(this);
		}
	}
}

const bool SpriteComponent::IsVisible()
{
	return m_IsVisible;
}

void SpriteComponent::Update(float deltaTime)
{
	UpdateSprite(deltaTime);
}

void SpriteComponent::TimedUpdate(float deltaTime)
{

}

void SpriteComponent::SetSrcRect(SDL_Rect *rect)
{
	if (m_Sprite != nullptr)
	{
		m_Sprite->SpriteSrcRect = *rect;
	}
}

void SpriteComponent::SetDestRect(SDL_Rect *rect)
{
	if (m_Sprite != nullptr)
	{
		m_Sprite->SpriteDestRect = *rect;
	}
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
