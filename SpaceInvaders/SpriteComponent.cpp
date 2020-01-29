#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
	:m_Sprite(new Sprite())
{
}

SpriteComponent::SpriteComponent(Entity &parent)
	:m_Sprite(new Sprite())
{
}

SpriteComponent::SpriteComponent(Entity &parent, SDL_Texture *texture)
	: m_Sprite(new Sprite())
{
	m_Sprite->pBitmapTexture = texture;
	Graphics::SetSrcRectFromTexture(m_Sprite->pBitmapTexture, m_Sprite->SpriteSrcRect);
	SyncParentToComponent();
	//Match the destination rect to the src as default;
	SetDestRect(&m_Sprite->SpriteSrcRect);
}

SpriteComponent::SpriteComponent(Entity &parent, SDL_Texture *texture, int spriteSheetIndex)
	: m_Sprite(new Sprite())
{
	SpriteComponent::SpriteComponent(parent, texture);
	m_Sprite->m_SpriteSheetIndex = spriteSheetIndex;
}


SpriteComponent::SpriteComponent(SDL_Texture * texture)
	: m_Sprite(new Sprite())
{
	m_Sprite->pBitmapTexture = texture;
	Graphics::SetSrcRectFromTexture(m_Sprite->pBitmapTexture, m_Sprite->SpriteSrcRect);
	//Match the destination rect to the src as default;
	SetDestRect(&m_Sprite->SpriteSrcRect);
}

SpriteComponent::~SpriteComponent()
{
	Graphics::RemoveSpriteFromDrawList(this);
	UpdateManager::ClearTimedUpdate(this);
	SAFE_DELETE(m_Sprite);
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
		if (visible)
		{
			if (m_Sprite->m_MaxFrames > 1)
			{
				UpdateManager::RegisterTimedUpdate(this);
			}
			Graphics::RegisterSpriteToDraw(this);
		}
		else
		{
			if (m_Sprite->m_MaxFrames > 1)
			{
				UpdateManager::SafeClearTimedUpdate(this);
			}
			Graphics::RemoveSpriteFromDrawList(this);
		}
		m_IsVisible = visible;
	}
}

const bool SpriteComponent::IsVisible()
{
	return m_IsVisible;
}

void SpriteComponent::Update(float deltaTime)
{
	
}

void SpriteComponent::TimedUpdate(float deltaTime)
{
	UpdateSprite(deltaTime);
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
		++(*m_Sprite);
		m_TimeSinceAnimUpdate = 0;
	}
}

void SpriteComponent::SetSpriteMaxFrame(int maxFrames)
{
	
	if (m_Sprite->m_MaxFrames != maxFrames)
	{
		//if it was a single frame
		if (maxFrames > 1 && IsVisible())
		{
			//We should register for updates so we can begin animations if they are available
			UpdateManager::RegisterTimedUpdate(this);
		}
		else if (maxFrames <= 1 && IsVisible())
		{
			//Safe Clear update if we are no longer animated;
			UpdateManager::SafeClearTimedUpdate(this);
		}
		m_Sprite->m_MaxFrames = maxFrames;
	}
}
