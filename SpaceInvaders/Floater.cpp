#include "Floater.h"
#include "TextComponent.h"
#include <sstream>

Floater::Floater(int value, SVector2D pos, float lifetime)
{
	std::stringstream ss;
	ss << value;
	SetupFloater(ss.str().c_str(), pos, lifetime);
}

Floater::Floater(const char* value, SVector2D pos, float lifetime)
{
	SetupFloater(value, pos, lifetime);
}

void Floater::Update(float deltaTime)
{
	m_CountDown -= deltaTime;
	if (m_CountDown <= 0 && !m_InfiniteLifetime)
	{
		CleanFloater();
	}
}

void Floater::SetupFloater(const char* value, SVector2D pos, float lifetime)
{
	TextComponent *sprite =	new TextComponent(*this,value);
	AddComponent(sprite);
	sprite->SetVisible(true);
	pos.x = pos.x - (sprite->m_Sprite->SpriteSrcRect.w / 2);
	pos.y = pos.y - (sprite->m_Sprite->SpriteDestRect.h / 2);
	SetPosition(pos);

	m_CountDown = lifetime;
	UpdateManager::RegisterUpdate(this);
	
	m_Active = true;
	if (lifetime < 0)
	{
		m_InfiniteLifetime = true;
	}
}

void Floater::UpdateFloater(const char * value, SDL_Color color)
{
	TextComponent *tc;
	if (TryGetComponent<TextComponent>(*this, tc))
	{
		tc->SetTextAndFontColor(value, color);
	}
}

void Floater::CleanFloater()
{
	UpdateManager::SafeClearUpdate(this);
	SpriteComponent *sprite;
	if (TryGetComponent<SpriteComponent>(*this, sprite))
	{
		sprite->SetVisible(false);
	}
	m_Active = false;
}

void Floater::OnSafeClear()
{
	delete this;
}

Floater::~Floater()
{
}
