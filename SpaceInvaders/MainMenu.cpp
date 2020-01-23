#include "MainMenu.h"

MainMenu::MainMenu()
	:m_GameTitle(new Entity())
{
	//Test Init Code========================== CLEAN ME=========================================
	m_GameTitle->AddComponent(new SpriteComponent(Graphics::LoadResource("Resources/logo.png")));
	SpriteComponent *component = nullptr;
	if (Entity::TryGetComponent<SpriteComponent>(*m_GameTitle, *&component))
	{
		component->SetVisible(true);
		component->m_Sprite->m_MaxFrames = 1;
		component->SetDestRect(&component->m_Sprite->SpriteSrcRect);
	}
}

MainMenu::~MainMenu()
{
}
