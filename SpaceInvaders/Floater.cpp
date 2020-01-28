#include "Floater.h"
#include <string>
Floater::Floater(int value, SVector2D pos, float lifetime)
{
	std::string s;
	s = value;
	SetupFloater(s.c_str(), pos, lifetime);
}


Floater::Floater(const char* value, SVector2D pos, float lifetime)
{
	SetupFloater(value, pos, lifetime);
}

void Floater::Update(float deltaTime)
{
	m_CountDown -= deltaTime;
	if (m_CountDown <= 0)
	{
		UpdateManager::SafeClearUpdate(this);
		SpriteComponent *sprite;
		if (TryGetComponent<SpriteComponent>(*this, sprite))
		{
			sprite->SetVisible(false);
		}
		m_Active = false;
	}
}

void Floater::SetupFloater(const char* value, SVector2D pos, float lifetime)
{
	SDL_Color color;
	color.r = 255;
	color.b = 0;
	color.g = 0;
	color.a = 255;
	SpriteComponent *sprite =
		new SpriteComponent(*this, Graphics::LoadTextSolid((char*)value, color));
	AddComponent(sprite);
	sprite->SetVisible(true);
	pos.x = pos.x - (sprite->m_Sprite->SpriteSrcRect.w / 2);
	pos.y = pos.y - (sprite->m_Sprite->SpriteDestRect.h / 2);
	SetPosition(pos);

	m_CountDown = lifetime;
	UpdateManager::RegisterUpdate(this);
	m_Active = true;
}

Floater::~Floater()
{
}
