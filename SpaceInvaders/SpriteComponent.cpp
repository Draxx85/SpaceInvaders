#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
	:m_Sprite(new Sprite())
{
}

SpriteComponent::SpriteComponent(Entity &parent)
	:m_Sprite(new Sprite())
{
	Component::Component(parent);
}

SpriteComponent::SpriteComponent(Entity &parent, SDL_Texture *texture)
	: m_Sprite(new Sprite())
{
	Component::Component(parent);
	m_Sprite->pBitmapTexture = texture;
	Graphics::SetSrcRectFromTexture(m_Sprite->pBitmapTexture, m_Sprite->SpriteSrcRect);
	SyncParentToComponent();
}


SpriteComponent::SpriteComponent(SDL_Texture * texture)
	: m_Sprite(new Sprite())
{
	m_Sprite->pBitmapTexture = texture;
	Graphics::SetSrcRectFromTexture(m_Sprite->pBitmapTexture, m_Sprite->SpriteSrcRect);
}

SpriteComponent::~SpriteComponent()
{
	delete m_Sprite;
}

void SpriteComponent::SyncParentToComponent()
{
	if (m_Parent != nullptr)
	{
		STransform *transform = m_Parent->GetTransform();
		if (transform != nullptr)
		{
			transform->SetDestRect(m_Sprite->SpriteDestRect);
		}
	}
}

void SpriteComponent::SetParent(Entity & component)
{
	Component::SetParent(component);
	SyncParentToComponent();
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

void SpriteComponent::UpdateSpritePos(SVector2D pos)
{
	if (m_Sprite != nullptr)
	{
		
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
